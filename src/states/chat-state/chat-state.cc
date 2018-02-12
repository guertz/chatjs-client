#include <iostream>
#include <map>
#include <json.hpp>
#include <cassert>

#include "chat-state.h"

#include "protocol/sockets/wscustom.h"
#include "common/logger/logger.h"

#include "states/auth-state/auth-state.h"
#include "protocol/sockets/wscustom.h"

using json = nlohmann::json;
using namespace std;
using namespace ws;

namespace States {

    namespace ChatState {

        typedef std::map<std::string, ws::Socket*> SocketsMap;

        static Chats        chatsList;

        static Socket *chatsSocket = 0;

        static SocketsMap   socketsChatsList;

        void Bootstrap(){

            chatsSocket = new Socket( "chats-stream", 
                            ChatsMethods::ResponseSuccess, 
                            ChatsMethods::ResponseError);
            AuthState::Register("ChatState", State::Auth);
        }

        void Destroy () {
            
            ChatsMethods::Clean();

            if(chatsSocket) {
                delete chatsSocket;
                chatsSocket = 0;
            }
        }

        namespace ChatMethods {

            Subscribers subscribed;

            void Register(std::string abc, void (*fn)()) {
                subscribed[abc] = fn;
            }

            inline void InitAChat(const Chat& chat){

                User auth_user = AuthState::getAuthUser();
                
                assert(auth_user.is_valid());

                socketsChatsList[chat.reference] = 
                    new Socket( "chats/" + chat.reference,  
                                ResponseSuccess, 
                                ResponseError);

                Request::Chat chat_join;
                    chat_join.type = TYPE::JOIN;

                BaseRequest socket_data;
                    socket_data.content = chat_join.serialize();
                    socket_data.AUTH = auth_user._id;

                assert(socketsChatsList[chat.reference]);

                socketsChatsList[chat.reference]->setBuffer(socket_data);
     

            }

            void SendAMessage(const std::string& text) {
                
                const string referral = ChatsMethods::getCurrent(); 
                User auth_user = AuthState::getAuthUser();

                assert(auth_user.is_valid());

                Request::Chat chat_send;
                    chat_send.type = TYPE::SEND;
                    chat_send.text = text;
                                            
                BaseRequest socket_data;
                    socket_data.content = chat_send.serialize();
                    socket_data.AUTH = auth_user._id;

                assert(socketsChatsList[referral]);
                socketsChatsList[referral]->setBuffer(socket_data);
            }

            inline void Notify() {
                for (const auto& item : subscribed) 
                    (*item.second)();
            }

            inline void ResponseSuccess(const string args){

                Response::Chat chat_send(args);
                Message m(json::parse(args));
                
                chatsList[chat_send.ref].messages.push_back(m);
                Notify();

            }

            inline void ResponseError(const string error) {
                
            }
        }

        namespace ChatsMethods {
            static Subscribers subscribed;
            static string currentChatRef;

            void Register(std::string abc, void (*fn)()) {
                
                subscribed[abc] = fn;
            }

            const string getSerializedChats() {

                json container;
                ChatsWrapper::chats_to_json(chatsList, container);
                return container.dump();
            }

            void setCurrent(const string& reference) {
                currentChatRef = reference;
                assert(currentChatRef.size());

                ChatMethods::Notify();
            }

            const string getCurrent() {
                return currentChatRef;
            }

            bool isCurrentChat() {
                return currentChatRef.size() > 0;
            }

            const string getCurrentChat() {

                assert(isCurrentChat());
                return chatsList[currentChatRef].serialize();

            }
        
            inline void Init(const string& AUTH) {

                Request::Chats connect_request;
                    connect_request.type = TYPE::CONNECT;
                    
                BaseRequest socket_data;
                    socket_data.content = connect_request.serialize();
                    socket_data.AUTH = AUTH;

                assert(chatsSocket);
                chatsSocket->setBuffer(socket_data);
                        
            }   

            inline void Notify() {
                for (const auto& item : subscribed) 
                    (*item.second)();
            }

            inline void Clean () {
                
                // will map.clear destroy pointers?
                // do i need pointers?
                // // unique || shared ptr?
                for (SocketsMap::iterator it = socketsChatsList.begin(); it != socketsChatsList.end(); ++it) {
                    if(it->second){
                        delete it->second;
                            it->second = 0;
                    }

                    // socketsChatsList.erase(it);
                }

                // // check size to know if actually deleated?

                chatsList.clear();
                currentChatRef = "";

                ChatsMethods::Notify();
                ChatMethods::Notify();
            }

            inline void ResponseSuccess(const std::string success) {

                Response::Chats chat_response(success);

                Chat new_chat(success);
                ChatMethods::InitAChat(new_chat);
                chatsList[chat_response.reference] = new_chat;
                
                ChatsMethods::Notify();
            }

            inline void ResponseError(const std::string error) {

            }

            // Chat with the same user
            void StartAChat(const string& user_dest){

                User auth_user = AuthState::getAuthUser();

                Request::Chats create;
                    create.type = TYPE::CREATE;
                    create.destination = user_dest;

                assert(auth_user.is_valid());
                                                
                BaseRequest socket_data;
                    socket_data.content = create.serialize();
                    socket_data.AUTH = auth_user._id;

                assert(chatsSocket);
                chatsSocket->setBuffer(socket_data);
                
            

            }
        }


        namespace State {
            void Auth() {
            
                const AuthState::SIGNAL 
                                auth_action = AuthState::getAuthAction();
                const User      auth_user   = AuthState::getAuthUser();

                switch(auth_action){
                    case AuthState::SIGNAL::LOGIN:

                        if(auth_user.is_valid())
                            ChatsMethods::Init(auth_user._id);
                    
                        break;

                    default:
                    
                        ChatsMethods::Clean();
                        break;

                }
                
            }
        }

    }
}

