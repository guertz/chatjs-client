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

    static Socket *channel; 

    void Bootstrap(){
        channel = new Socket("chats-stream", Sockets::NewChat);

        AuthState::Register("ChatState", Auth::State);

        try {
            channel->compute();
        } catch(...) {
            log_base("ChatState", "socket error");
        }
    }

    // Destroy => stop & delete

    namespace Sockets {
        void Init(const char* user){

            cout<<user<<endl;
            // if(!channel){
                json jReq;
                     jReq["type"] = "connect";
                     jReq["_id"] = user;
                     
                     
                channel->setBuffer(jReq.dump(), true);

                cout<<"Socket initialized here"<<endl;
                
            // }

            safeptr::free_block(user);
        }

        void NewMessage(const char* args){

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

            safeptr::free_block(args);
        }

        void NewChat(const char* args){

            // server return also destination per user with details
            json jAuth    = json::parse(AuthState::getAuthStatus());
            json Chatters = json::parse(args);

            string referral = Chatters["reference"].get<string>();

            // todo, clean this mess
            // not ok, should instead push to current list dispatched to component
            chat_watchers[referral] = new Socket("chats/"+referral,  ChatState::Sockets::NewMessage);

            json jChatJoin = R"(
                        {
                            "type": "join",
                            "content": {
                                "_id": "fakecontent"
                            }
                        }
                    )"_json;

                jChatJoin["content"]["_id"] = jAuth["_id"];

            chat_watchers[referral]->setBuffer(jChatJoin.dump(), true);  

            // destination is always me when receiving
            chat_details details;
                details.reference = safestr::duplicate(referral.c_str());
                details.destination = safestr::duplicate(Chatters["destination"].dump().c_str());
                details.from = safestr::duplicate(Chatters["from"].dump().c_str());
                details.creator = safestr::duplicate(Chatters["creator"].dump().c_str());

            chat_list[referral] = details; // messages
            
            ChatState::Chats::Notify(safestr::duplicate(args));
            safeptr::free_block(args);
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
    
    
            json jArgs = json::parse(args);
            json jAuth = json::parse(AuthState::getAuthStatus());

            json communicate = R"(
                {
                    "type": "send",
                    "auth": {
                        "key": "fakeauth"
                    },
                    "content": {
                        "text": "fakemsg"
                    }
                }
            )"_json;

            communicate["auth"]["key"] = jAuth["_id"].get<string>();
            communicate["content"]["text"] = jArgs["text"].get<string>();


            chat_watchers[jArgs["reference"].get<string>()]->setBuffer(communicate.dump(), true);  

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

        void StartAChat(const char* args){

            json jParam = json::parse(args);

            // better data rapresentation with serializators
            json jReq;
                 jReq["type"] = "create";
                 jReq["destination"] = jParam["destination"];
                 
            channel->setBuffer(jReq.dump(), true);

            safeptr::free_block(args);
        }
    }

    namespace Auth {
        void State(const char* args){
            json jDat = json::parse(args);
            
            switch(jDat["action"].get<AuthState::AUTHSIGNAL>()){
                case AuthState::AUTHSIGNAL::LOGIN:
                    if(jDat["online"].get<bool>()){
                        
                        Sockets::Init(safestr::duplicate(jDat["_id"].get<string>().c_str()));
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

