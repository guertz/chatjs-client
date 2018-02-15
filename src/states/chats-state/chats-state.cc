#include <iostream>
#include <map>
#include <json.hpp>
#include <cassert>

#include "chats-state.h"

#include "protocol/sockets/wscustom.h"
#include "common/logger/logger.h"

#include "states/auth-state/auth-state.h"

/**
 * @brief Definizione stato gestione chat
 * @file chats-state.cc
 */

using json = nlohmann::json;
using namespace std;
using namespace ws;

namespace States {

    namespace ChatsState {

        // Definizione privata (interna) di tipo di dato
        typedef std::map<std::string, ws::Socket*> SocketsMap;

        /** 
         * Puntatore al canale di comunicazione aperto. 
         * In questo caso fa riferimento all'enpoint 'chats-stream'
         * sul server websocket
         */
        static Socket *chatsSocket = 0;

        /**
         * Mappa di puntatore ai canali di comunicazione aperti 
         * per ciascuna delle chat aperte
         */
        static SocketsMap   socketsChatsList;

        /** Lista di chats aperte */
        static Chats chatsList;

        /** Identificativo riferimento chat attualmente selezionata e attiva */
        static string currentChatRef;

        /** Mappa dei componenti che hanno sottoscritto allo stato */
        static Subscribers subscribed;

        void Register(std::string cb_name, void (*cb_fn)()) {
            log_C(TAG::STA, "States::ChatsState::Register", cb_name);

            subscribed[cb_name] = cb_fn;
        }

        void Bootstrap(){
            log_B(TAG::STA, "States::ChatsState::Bootstrap", "");

            chatsSocket = new Socket("chats-stream", 
                            ChatsSocketMethods::ResponseSuccess, 
                            ChatsSocketMethods::ResponseError);
                            
            AuthState::Register("ChatsState", State::Auth);
        }

        void Destroy () {
            log_B(TAG::STA, "States::ChatsState::Destroy", "");

            ChatsSocketMethods::CloseChannelSession();

            assert(chatsSocket);

            chatsSocket->syncDelete();
            delete chatsSocket;
                   chatsSocket = 0;
            
        }

        void StartAChat(const std::string user_dest) {

            User auth_user = AuthState::getAuthUser();
            assert(auth_user.is_valid());

            ChatsSocket::ChatsRequest create;
                create.type = ChatsSocket::SIGNAL::CREATE;
                create.destination = user_dest;            
                                            
            BaseRequest socket_data;
                socket_data.content = create.serialize();
                socket_data.AUTH = auth_user._id;

            chatsSocket->setBuffer(socket_data);
        }

        const std::string getSerializedChats() {
            return ChatsWrapper::chats_to_json(chatsList).dump();
        }

        void setCurrentChat(const std::string chat_ref) {
            assert(chat_ref.size());
            currentChatRef = chat_ref;

            ChatMethods::NotifyCurrent();
        }

        bool isCurrentChat() {
            return currentChatRef.size() > 0;
        }

        const std::string getCurrentChatRef() {
            return currentChatRef;
        }

        const std::string getCurrentChat() {
            assert(isCurrentChat());
            return chatsList[currentChatRef].serialize();
        }

        inline void Notify(){
            log_B(TAG::STA, "States::ChatsState::Notify", "State changes");

            for (const auto& subscription : subscribed) {
                log_C(TAG::STA, "States::ChatsState::Notify", subscription.first);
                (*subscription.second)(); 
            }
        }

        namespace ChatsSocketMethods {

            inline void InitChannelSession(const std::string& AUTH) {

                ChatsSocket::ChatsRequest connect_request;
                        connect_request.type = ChatsSocket::SIGNAL::CONNECT;
                    
                BaseRequest socket_data;
                    socket_data.content = connect_request.serialize();
                    socket_data.AUTH = AUTH;

                chatsSocket->setBuffer(socket_data);
                        
            }   

            inline void CloseChannelSession () {

                for (SocketsMap::iterator it = socketsChatsList.begin(); it != socketsChatsList.end(); ++it) {
                    it->second->syncDelete();
                    
                    delete  it->second;
                    // it->second = 0;

                    socketsChatsList.erase(it);

                }

                chatsList.clear();
                currentChatRef = "";

                Notify();
                ChatMethods::NotifyCurrent();

            }

            inline void ResponseSuccess(const std::string str_response) {

                ChatsSocket::ChatsResponse chat_response(str_response);

                chatsList[chat_response.reference] = Chat(str_response);
                ChatMethods::ChatSocketMethods::InitChannelSession(
                        chatsList[chat_response.reference]);
                
                Notify();
            }

            inline void ResponseError(const std::string str_error) {

            }

        }

        namespace ChatMethods {

            // TODO: Muovi a lista di sottoscritti per chat (ciascuna)
            /** Mappa dei componenti che hanno sottoscritto per eventi delle singole chat */
            static Subscribers chat_subscribed;

            void Register(std::string cb_name, void (*cb_fn)()) {
                chat_subscribed[cb_name] = cb_fn;
            }

            // TODO: move in chatSocket
            void SendAMessage(const std::string text) {
                
                User auth_user = AuthState::getAuthUser();
                assert(auth_user.is_valid());

                ChatSocket::ChatRequest chat_send;
                    chat_send.type = ChatSocket::SIGNAL::SEND;
                    chat_send.text = text;
                                            
                BaseRequest socket_data;
                    socket_data.content = chat_send.serialize();
                    socket_data.AUTH = auth_user._id;
        
                socketsChatsList[getCurrentChatRef()]->setBuffer(socket_data);
            }

            inline void NotifyCurrent(){
                log_B(TAG::STA, "States::ChatsState::Notify(Chat)", "Current chat state: '" + currentChatRef + "' changes");

                for (const auto& subscription : chat_subscribed) {
                    log_C(TAG::STA, "States::ChatsState::Notify(Chat)", subscription.first);
                    (*subscription.second)(); 
                }
            }

            namespace ChatSocketMethods {

                inline void InitChannelSession(const Chat& chat){

                    User auth_user = AuthState::getAuthUser();
                    assert(auth_user.is_valid());

                    socketsChatsList[chat.reference] = 
                        new Socket("chats/" + chat.reference,  
                                    ResponseSuccess, 
                                    ResponseError);

                    ChatSocket::ChatRequest chat_join;
                        chat_join.type = ChatSocket::SIGNAL::JOIN;

                    BaseRequest socket_data;
                        socket_data.content = chat_join.serialize();
                        socket_data.AUTH = auth_user._id;

                    socketsChatsList[chat.reference]->setBuffer(socket_data);
                }

                inline void ResponseSuccess(const std::string str_response){

                    ChatSocket::ChatResponse chat_response(str_response);

                    chatsList[chat_response.ref].messages.push_back(Message(str_response));
                    NotifyCurrent();

                }

                inline void ResponseError(const std::string str_error) {
                    
                }

            }
        }

        namespace State {
            void Auth() {
            
                const AuthSocket::SIGNAL 
                                auth_action = AuthState::getAuthAction();
                const User      auth_user   = AuthState::getAuthUser();

                switch(auth_action){
                    case AuthSocket::SIGNAL::LOGIN:

                        if(auth_user.is_valid())
                            ChatsSocketMethods::InitChannelSession(auth_user._id);
                    
                        break;

                    default:
                    
                        ChatsSocketMethods::CloseChannelSession();
                        break;

                }
                
            }
        }

    }
}

