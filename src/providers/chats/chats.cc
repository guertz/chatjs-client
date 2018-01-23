#include <json.hpp>
#include <string>
#include "chats.h"
#include "chat.h"
#include "protocol/sockets/wscustom.h"
#include "states/auth-state/auth-state.h"
#include "common/helpers/helpers.h"
#include "common/logger/logger.h"

using json = nlohmann::json;
using namespace std;
using namespace ws;
using namespace Helpers;
using namespace States;

namespace ChatState {

    static typo_chats         chat_list;
    static typo_chat_watchers chat_watchers;

    static Socket *channel = 0; 

    void Bootstrap(){
        
        try {
            channel = new Socket(   "chats-stream", 
                                    Sockets::NewChatSuccess, 
                                    Sockets::NewChatError);
        } catch(...) {
            log_base("ChatState::Socket>>'chats-stream'", "Exception reported");
        }

        AuthState::Register("ChatState", Auth::State);


    }

    void Destroy () {
        // Use method
        if(channel){
            delete channel;
                   channel = 0;
        }
    }

    namespace Sockets {
        void Init(const string user){

            // if(!channel){

            json connect_request = {{"type", "connect"}, {"user", user}};

            RequestDefinition::Request request = RequestDefinition::createEmpty();
                
                request.content =  connect_request.dump();
                
            channel->setBuffer(request);
                
            // }
        }

        void NewMessageSuccess(const string args){

            json jChat = json::parse(args);

            const char* chat = jChat["ref"].get<string>().c_str();
            const char* msg = jChat["msg"].get<string>().c_str();

            message_block t;

                t.content = safestr::duplicate(jChat["data"]["content"].get<string>().c_str());
                t.status = ACK_LEVEL::WAITING;
                t.isMe   = jChat["data"]["isMe"].get<bool>();   
                t.avatar = safestr::duplicate(jChat["data"]["sender"]["image"].get<string>().c_str());
                t.time   = safestr::duplicate(jChat["data"]["time"].get<string>().c_str());


            chat_list[chat].messages[msg] = t;

            ChatState::Chat::Notify(safestr::duplicate("{}")); // args?

            safeptr::free_block(chat);
            safeptr::free_block(msg);

        }

        void NewMessageError(const string error) {

        }

        void NewChatSuccess(const string args){

            const char* userInSession = AuthState::getAuthStatus();

            json chat_args = json::parse(args);
            string referral = chat_args.at("reference").get<string>();

            if(userInSession){

                json auth_user = json::parse(userInSession).at("content");
                
                auth_user.at("_id").get<string>();

                try { 
                    chat_watchers[referral] = new Socket("chats/"+referral,  ChatState::Sockets::NewMessageSuccess, NewMessageError);

                    json chat_join_request{
                            { "type", "join"},
                            { "content", 
                                { "_id", auth_user.at("_id").get<string>() }
                            }
                        };
                    
                    RequestDefinition::Request request = RequestDefinition::createEmpty();
                        request.content = chat_join_request.dump();

                        chat_watchers[referral]->setBuffer(request);

                } catch(...) {
                    log_base(("ChatState::Socket>>'chats/" + referral + "'").c_str(), "Exception reported");
                }
            } 

            // destination is always me when receiving
            chat_details details;
                details.reference = safestr::duplicate(referral.c_str());
                details.destination = safestr::duplicate(chat_args["destination"].dump().c_str());
                details.from = safestr::duplicate(chat_args["from"].dump().c_str());
                details.creator = safestr::duplicate(chat_args["creator"].dump().c_str());

            chat_list[referral] = details; // messages
            
            ChatState::Chats::Notify(safestr::duplicate(args.c_str()));
        }

        void NewChatError(const string args) {

        }
    }

    namespace Chat {

        Methods subscribers;

        void Register(string component, void (*fn)(const char* arg)){
            subscribers[component] = fn;
        }

        void Notify(const char* args){

            for (const auto& item : subscribers) 
                (*item.second)(safestr::duplicate(args));
            
            safeptr::free_block(args);

        }

        const chat_details& Get(const char* chatReference){
            return chat_list[chatReference];
        }

        void SendAMessage(const char* args){

            const char* userInSession = AuthState::getAuthStatus();
    
            json jArgs = json::parse(args);

            // TODO, change on server because needs to validate as authenticated
            //       this json structure changed
            // 
            //     Using auth headers + new content format
            json communicate{
                    {"type", "send"},
                    {"text", jArgs["text"].get<string>()}
                };

            if(userInSession){
                json auth_user = json::parse(userInSession).at("content");

                RequestDefinition::Request request = 
                    RequestDefinition::createAuthenticated(auth_user.at("_id").get<string>());
                    
                    request.content =  communicate.dump();

                chat_watchers[jArgs["reference"].get<string>()]->setBuffer(request);  
            }

        }

    }

    namespace Chats {
        
        Methods subscribers;

        void Register(string component, void (*fn)(const char* arg)){
            subscribers[component] = fn;
        }

        const typo_chats& Get(){
            return chat_list;
        }

        void Notify(const char* args){

            for (const auto& item : subscribers) 
                (*item.second)(safestr::duplicate(args));
            
            safeptr::free_block(args);
        }

        void StartAChat(const string user_dest){

            json create_chat_request = {{"type", "create"}, {"destination", user_dest}};

            RequestDefinition::Request request = RequestDefinition::createEmpty();
                
                request.content =  create_chat_request.dump();
                
            channel->setBuffer(request);

        }
    }

    namespace Auth {
        void State(const char* args){
            json jDat = json::parse(args);
            
            switch(jDat["action"].get<AuthState::AUTHSIGNAL>()){
                case AuthState::AUTHSIGNAL::LOGIN:
                    if(jDat["online"].get<bool>()){
                        
                        Sockets::Init(jDat["_id"].get<string>());
                    }
                    break;
                case AuthState::AUTHSIGNAL::LOGOUT:
                
                        // ChatState::Broker::clean();
                    break;
            }

            safeptr::free_block(args);
            
        }
    }

}

