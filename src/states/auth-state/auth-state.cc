#include <iostream>
#include <map>
#include <json.hpp>

#include "auth-state.h"
#include "protocol/sockets/wscustom.h"

#include "common/logger/logger.h"

using json = nlohmann::json;
using namespace ws;
using namespace std;

/**
 * @brief Definizione stato di autenticazione utenti
 * @file auth-state.cc
 */


namespace States {
    
    namespace AuthState {

        /** 
         * Puntatore al canale di comunicazione aperto. 
         * In questo caso fa riferimento all'enpoint 'auth'
         * sul server websocket
         */
        static Socket* authSocket = 0;

        /** Specifica se vi sono altre azioni di login in corso */
        static bool pending = false;
        
        /** Tiene traccia dell'ultima risposta ricevuta */
        static AuthSocket::AuthResponse authResponse;

        /** Mappa dei componenti che hanno sottoscritto allo stato */
        static Subscribers subscribed;

        void Register(std::string cb_name, void (*cb_fn)()) {
            log_C(TAG::STA, "States::AuthState::Register", cb_name);

            subscribed[cb_name] = cb_fn;
        }

        void Bootstrap() {
            log_B(TAG::STA, "States::AuthState::Bootstrap", "");

            authSocket = new Socket("auth", 
                                AuthSocketMethods::ResponseSuccess, 
                                AuthSocketMethods::ResponseError);

        }

        void Destroy() {
            log_B(TAG::STA, "States::AuthState::Destroy", "");

            assert(authSocket);
            
            authSocket->syncDelete();
            delete authSocket;
                   authSocket = 0;
        }

        void Login(const std::string& AUTH_KEY){
            log_C(TAG::STA, "States::AuthState::Login", AUTH_KEY);

            // verifica condizioni base elementari per poter
            // effettuare una richiesta di questo tipo
            assert(!pending && !authResponse.online);

            pending = true;
            
            // Preparazione della richiesta ad alto livello
            AuthSocket::AuthRequest auth_request;
                auth_request.type = AuthSocket::SIGNAL::LOGIN;
                auth_request.user = AUTH_KEY;

            // Preparazione della richiesta a livello più basso
            BaseRequest socket_data;
                        socket_data.content = auth_request.serialize();

            // Invio della richiesta sul buffer del canale
            authSocket->setBuffer(socket_data);

        }

        // Fare riferimento a Login per la descrizione dei vari step
        void Logout(){
            log_C(TAG::STA, "States::AuthState::Logout", "");

            assert(!pending && authResponse.online);
            pending = true;


            AuthSocket::AuthRequest auth_request;
                auth_request.type = AuthSocket::SIGNAL::LOGOUT;

            
            BaseRequest socket_data;
                        socket_data.content = auth_request.serialize();
                        // Fa riferimento all'utente attualmente connesso
                        socket_data.AUTH    = authResponse.user._id;

            authSocket->setBuffer(socket_data);

        }

        AuthSocket::SIGNAL getAuthAction() {
            return authResponse.type;
        }

        User getAuthUser() {
            return authResponse.user;
        }

        std::string getAuthError() {
            return authResponse.error;
        }

        inline void Notify(){
            log_B(TAG::STA, "States::AuthState::Notify", "State changes");

            for (const auto& subscription : subscribed) {
                log_C(TAG::STA, "States::AuthState::Notify", subscription.first);
                (*subscription.second)(); 
            }
        }
        
        namespace AuthSocketMethods {

            inline void ResponseSuccess(const std::string str_response) {
                log_C(TAG::STA, "States::AuthState::Response", str_response);

                // namespace inheritance
                authResponse = AuthSocket::AuthResponse(str_response);
                pending = false;

                Notify();
            }

            inline void ResponseError(const std::string str_error) {
                log_C(TAG::STA, "States::AuthState::Response", str_error);

                // namespace inheritance
                AuthSocket::AuthResponse response_errors;
                        response_errors.type  = AuthSocket::SIGNAL::LOGIN; 
                        response_errors.error = str_error;

                authResponse = response_errors;
                pending = false;

                Notify();
            }

        }

    }
}