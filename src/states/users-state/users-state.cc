#include <iostream>
#include <map>
#include <json.hpp>

#include "users-state.h"
#include "states/auth-state/auth-state.h"

#include "protocol/sockets/wscustom.h"

#include "common/logger/logger.h"

using json = nlohmann::json;
using namespace ws;
using namespace std;

/**
 * @brief Definizione stato di autenticazione utenti
 * @file users-state.cc
 */

namespace States {

    namespace UsersState {

        /** 
         * Puntatore al canale di comunicazione aperto. 
         * In questo caso fa riferimento all'enpoint 'users-stream'
         * sul server websocket
         */
        static Socket *usersSocket = 0;

        /** Specifica se vi sono altre azioni in corso sul canale*/
        static bool pending = false;

        /** Tiene traccia dell'ultima risposta ricevuta */
        static UsersSocket::UsersResponse usersResponse;

        /** Mappa dei componenti che hanno sottoscritto allo stato */
        static Subscribers subscribed;

        void Register(std::string cb_name, void (*cb_fn)()) {
            log_C(TAG::STA, "States::UsersState::Register", cb_name);

            subscribed[cb_name] = cb_fn;
        }

        void Bootstrap() {
            log_B(TAG::STA, "States::UsersState::Bootstrap", "");

            AuthState::Register("UsersState", State::Auth);

            usersSocket = new Socket("users-stream", 
                                UsersSocketMethods::ResponseSuccess, 
                                UsersSocketMethods::ResponseError);

        }

        void Destroy() {
            log_B(TAG::STA, "States::UsersState::Destroy", "");

            assert(usersSocket);
            delete usersSocket;
                   usersSocket = 0;
        
        }

        const std::string& getSerializedList() {
            return usersResponse.usersList;    
        }
        
        inline void Notify(){

            log_B(TAG::STA, "States::UsersState::Notify", "State changes");

            for (const auto& subscription : subscribed) {
                log_C(TAG::STA, "States::UsersState::Notify", subscription.first);
                (*subscription.second)(); 
            }
            
        }

        namespace UsersSocketMethods {
            inline void InitChannelSession(const std::string& AUTH) {
                log_B(TAG::STA, "States::UsersState::InitChannelSession", AUTH);

                assert(!pending);
                pending = true;
            
                UsersSocket::UsersRequest users_request;
                        users_request.type = UsersSocket::SIGNAL::OPEN;

                    
                BaseRequest socket_data;
                    socket_data.content = users_request.serialize();
                    socket_data.AUTH = AUTH;

                usersSocket->setBuffer(socket_data);
                
            }

            inline void CloseChannelSession() {
                log_B(TAG::STA, "States::UsersState::Close", "");

                assert(pending);
                pending = false;

                UsersSocket::UsersRequest users_request;
                        users_request.type = UsersSocket::SIGNAL::CLOSE;

                
                BaseRequest socket_data;
                    socket_data.content = users_request.serialize();

                usersSocket->setBuffer(socket_data);
                
            }

            inline void ResponseSuccess(const std::string str_response) {
                log_C(TAG::STA, "States::UsersState::Response", str_response);

                usersResponse = UsersSocket::UsersResponse(str_response);

                Notify();
            }

            inline void ResponseError(const std::string str_error) {
                
                usersResponse = UsersSocket::UsersResponse();

                Notify();
            }
        
        }

        namespace State {

            void Auth() {

                const AuthSocket::SIGNAL 
                                auth_action = AuthState::getAuthAction();
                const User      auth_user   = AuthState::getAuthUser();

                switch(auth_action) {

                    case AuthSocket::SIGNAL::LOGIN:

                        if(auth_user.is_valid())
                            UsersSocketMethods::InitChannelSession(auth_user._id);

                        break;

                    default:

                        UsersSocketMethods::CloseChannelSession();
                        break;
                    
                }
                
            }
        }
    }
}