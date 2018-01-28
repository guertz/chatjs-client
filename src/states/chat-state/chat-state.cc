#include <iostream>
#include <map>
#include <json.hpp>

#include "chat-state.h"

#include "protocol/sockets/wscustom.h"
#include "common/helpers/helpers.h"
#include "common/logger/logger.h"

#include "states/auth-state/auth-state.h"
#include "protocol/sockets/wscustom.h"

using json = nlohmann::json;
using namespace std;
using namespace ws;
using namespace Helpers;
using namespace States;

namespace States {
    namespace ChatState {

        static Chats        chats;
        static SocketsMap   chats_socket;

        // TODO: register in its proper namespace
        static Socket *channel = 0; 

        void Bootstrap(){
            
            try {
                channel = new Socket(   "chats-stream", 
                                        ChatsMethods::ResponseSuccess, 
                                        ChatsMethods::ResponseError);
            } catch(...) {
                log_base("ChatState::Socket>>'chats-stream'", "Exception reported");
            }

            AuthState::Register("ChatState", State::Auth);


        }

        void Destroy () {
            // Use method
            if(channel){
                delete channel;
                    channel = 0;
            }
        }

        // inline void Init(const string& user){

            // if(!channel){

            // json connect_request = {{"type", "connect"}, {"user", user}};

            // RequestDefinition::Request request = RequestDefinition::createEmpty();
                
            //     request.content =  connect_request.dump();
                
            // channel->setBuffer(request);
                
            // }
        // }

        namespace ChatMethods {

            Subscribers subscribed;

            void Register(std::string abc, void (*fn)()) {
                subscribed[abc] = fn;
            }

            const Chat& getChatByRef(const std::string& referral) {

            }

            void SendAMessage(const std::string& msg) {
                // const AuthState::AUTHSIGNAL auth_action = AuthState::getAuthAction();
                //                  User       auth_user   = AuthState::getAuthUser();

        
                // json jArgs = json::parse(args);

                // // TODO, change on server because needs to validate as authenticated
                // //       this json structure changed
                // // 
                // //     Using auth headers + new content format
                // json communicate{
                //         {"type", "send"},
                //         {"text", jArgs["text"].get<string>()}
                //     };

                // if(auth_user.is_valid()){

                //     // RequestDefinition::Request request = 
                //     //     RequestDefinition::createAuthenticated(auth_user._id);
                        
                //     //     request.content =  communicate.dump();

                //     // chat_watchers[jArgs["reference"].get<string>()]->setBuffer(request);  
                // }
            }

            inline void Notify() {
                for (const auto& item : subscribed) 
                    (*item.second)();
            }

            inline void ResponseSuccess(const string args){

                // json jChat = json::parse(args);

                // const string chat = jChat["ref"].get<string>();
                // const string msg = jChat["msg"].get<string>();

                // message_block t;

                //     t.content = jChat["data"]["content"].get<string>();
                //     t.status = ACK_LEVEL::WAITING;
                //     t.isMe   = jChat["data"]["isMe"].get<bool>();   
                //     t.avatar = jChat["data"]["sender"]["image"].get<string>();
                //     t.time   = jChat["data"]["time"].get<string>();


                // chat_list[chat].messages[msg] = t;

                // ChatState::Chat::Notify();
            }

            inline void ResponseError(const string error) {

            }
        }

        namespace ChatsMethods {
            Subscribers subscribed;

            void Register(std::string abc, void (*fn)()) {
                subscribed[abc] = fn;
            }

            const Chats& getChatsByRef() {

            }

            inline void Notify() {
                for (const auto& item : subscribed) 
                    (*item.second)();
            }

            inline void ResponseSuccess(const std::string success) {

                // const AuthState::AUTHSIGNAL auth_action = AuthState::getAuthAction();
                //                 User       auth_user   = AuthState::getAuthUser();

                // json chat_args = json::parse(args);
                // string referral = chat_args.at("reference").get<string>();

                // if(auth_user.is_valid()){

                //     try { 
                //         chat_watchers[referral] = new Socket("chats/"+referral,  NewMessageSuccess, NewMessageError);

                //         json chat_join_request{
                //                 { "type", "join"},
                //                 { "content", 
                //                     { "_id", auth_user._id }
                //                 }
                //             };
                        
                //         // RequestDefinition::Request request = RequestDefinition::createEmpty();
                //         //     request.content = chat_join_request.dump();

                //         //     chat_watchers[referral]->setBuffer(request);

                //     } catch(...) {
                //         log_base(("ChatState::Socket>>'chats/" + referral + "'").c_str(), "Exception reported");
                //     }
                // } 

                // // destination is always me when receiving
                // // dump => because i need user data, view may need an update
                // chat_details details;
                //     details.reference = referral;
                //     details.destination = chat_args["destination"].dump();
                //     details.from = chat_args["from"].dump();
                //     details.creator = chat_args["creator"].dump();

                // chat_list[referral] = details;
                
                // ChatState::Chats::Notify(args);
            }

            inline void ResponseError(const std::string error) {

            }
        

            void StartAChat(const string& user_dest){

                json create_chat_request = {{"type", "create"}, {"destination", user_dest}};

                // RequestDefinition::Request request = RequestDefinition::createEmpty();
                    
                //     request.content =  create_chat_request.dump();
                    
                // channel->setBuffer(request);

            }
        }


        namespace State {
            void Auth() {
                
                const AuthState::AUTHSIGNAL auth_action = AuthState::getAuthAction();
                                 User       auth_user   = AuthState::getAuthUser();

                switch(auth_action){
                    case AuthState::AUTHSIGNAL::LOGIN:

                        if(auth_user.is_valid())
                            // Sockets::Init(auth_user._id);
                        

                        break;
                    case AuthState::AUTHSIGNAL::LOGOUT:
                    
                            // ChatState::Broker::clean();
                        break;

                    case AuthState::AUTHSIGNAL::ALL:
                    default:
                    
                        log_base("AuthModal", "Bad format Request");
                        break;
                }
                
            }
        }

    }
}

