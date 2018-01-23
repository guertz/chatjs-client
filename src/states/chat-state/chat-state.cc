#include <iostream>
#include <map>
#include <json.hpp>

// and all the required definitions
#include "chat-state.h"

#include "protocol/sockets/wscustom.h"
#include "common/helpers/helpers.h"
#include "common/logger/logger.h"

#include "states/auth-state/auth-state.h"

using json = nlohmann::json;
using namespace std;
using namespace ws;
using namespace Helpers;
using namespace States;

namespace States {
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
            void Init(const string& user){

                // if(!channel){

                json connect_request = {{"type", "connect"}, {"user", user}};

                RequestDefinition::Request request = RequestDefinition::createEmpty();
                    
                    request.content =  connect_request.dump();
                    
                channel->setBuffer(request);
                    
                // }
            }

            void NewMessageSuccess(const string args){

                json jChat = json::parse(args);

                const string chat = jChat["ref"].get<string>();
                const string msg = jChat["msg"].get<string>();

                message_block t;

                    t.content = jChat["data"]["content"].get<string>();
                    t.status = ACK_LEVEL::WAITING;
                    t.isMe   = jChat["data"]["isMe"].get<bool>();   
                    t.avatar = jChat["data"]["sender"]["image"].get<string>();
                    t.time   = jChat["data"]["time"].get<string>();


                chat_list[chat].messages[msg] = t;

                ChatState::Chat::Notify();
            }

            void NewMessageError(const string error) {

            }

            void NewChatSuccess(const string args){

                const AuthState::UserDefinition::User& auth_user = AuthState::getAuthUser();

                json chat_args = json::parse(args);
                string referral = chat_args.at("reference").get<string>();

                // class->isLogged
                if(auth_user._id.size()>0){

                    try { 
                        chat_watchers[referral] = new Socket("chats/"+referral,  NewMessageSuccess, NewMessageError);

                        json chat_join_request{
                                { "type", "join"},
                                { "content", 
                                    { "_id", auth_user._id }
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
                // dump => because i need user data, view may need an update
                chat_details details;
                    details.reference = referral;
                    details.destination = chat_args["destination"].dump();
                    details.from = chat_args["from"].dump();
                    details.creator = chat_args["creator"].dump();

                chat_list[referral] = details;
                
                ChatState::Chats::Notify(args);
            }

            void NewChatError(const string args) {

            }
        }

        namespace Chat {

            Methods_void subscribers;

            void Register(string component, void (*fn)()){
                subscribers[component] = fn;
            }

            void Notify(){

                for (const auto& item : subscribers) 
                    (*item.second)();
            }

            const chat_details& Get(const string& chat_reference){
                return chat_list[chat_reference];
            }

            void SendAMessage(const string& args){

                const AuthState::UserDefinition::User& auth_user = AuthState::getAuthUser();
        
                json jArgs = json::parse(args);

                // TODO, change on server because needs to validate as authenticated
                //       this json structure changed
                // 
                //     Using auth headers + new content format
                json communicate{
                        {"type", "send"},
                        {"text", jArgs["text"].get<string>()}
                    };

                if(auth_user._id.size()>0){

                    RequestDefinition::Request request = 
                        RequestDefinition::createAuthenticated(auth_user._id);
                        
                        request.content =  communicate.dump();

                    chat_watchers[jArgs["reference"].get<string>()]->setBuffer(request);  
                }

            }

        }

        namespace Chats {
            
            Methods subscribers;

            void Register(string component, void (*fn)(const string& arg)){
                subscribers[component] = fn;
            }

            const typo_chats& Get(){
                return chat_list;
            }

            void Notify(const string& args){

                for (const auto& item : subscribers) 
                    (*item.second)(args);
                
            }

            void StartAChat(const string& user_dest){

                json create_chat_request = {{"type", "create"}, {"destination", user_dest}};

                RequestDefinition::Request request = RequestDefinition::createEmpty();
                    
                    request.content =  create_chat_request.dump();
                    
                channel->setBuffer(request);

            }
        }

        namespace Auth {
            void State(const AuthState::AuthBaseDefinition::AuthBase& auth_data) {
                
                switch(auth_data.action){
                    case AuthState::AUTHSIGNAL::LOGIN:

                        if(auth_data.online)
                            Sockets::Init(auth_data.user._id);
                        

                        break;
                    case AuthState::AUTHSIGNAL::LOGOUT:
                    
                            // ChatState::Broker::clean();
                        break;
                }
                
            }
        }

    }
}

