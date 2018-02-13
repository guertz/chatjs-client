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

        // Dichiarazione metodi non definiti a livello di interfaccia

        /**
         * Metodo per inizializzare il socket usersSocket a seguito dell'azione di login
         *
         * @param AUTH
         */
        inline void Init(const std::string& AUTH);

        /** Metodo per chiudere il socket usersSocket a seguito dell'azione di logout */
        inline void Close();

        /**
         * Metodo per gestire l'avvenuta ricezione nel corretto formato
         * a seguito di un azione di tipo USERSSIGNAL sul canale di comunicazione
         * socket usersSocket.
         *
         * @param str_response Messaggio di risposta in formato JSON serializzato
         */
        inline void ResponseSuccess(const std::string str_response);

        /**
         * Metodo per gestire l'avvenuta ricezione di un messaggio di errore a 
         * seguito di un azione di tipo USERSSIGNAL sul canale di comunicazione
         * socket usersSocket.
         *
         * @param str_error Messaggio di errore stringa testo
         */
        inline void ResponseError(const std::string str_error);
        
        /** 
         * Metodo per notificare cambiamenti di stato ai componenti che
         * hanno sottoscritto allo stato di users
         */
        inline void Notify();

        // Variabile che contiene il puntatore al canale di comunicazione 
        // websocket all'endpoint 'users-stream' e ha durata di vita per tutto il
        // corso del programma
        static Socket *usersSocket = 0;

        // Variabile in cui viene mantenuto il contenuto a seguito di una risposta
        // da parte del canale di comunicazione usersSocket
        static UsersSocket::Response usersResponse;

        // Mappa dei componenti che sottoscrivono ad eventi relativi allo stato
        // di autenticazione
        static Subscribers subscribed;

        // Determina se il canale è già in ascolto della lista di utenti
        static bool pending = false;

        void Register(std::string cb_name, void (*cb_fn)()) {
            log_C(TAG::STA, "States::ChatState::Register", cb_name);

            subscribed[cb_name] = cb_fn;
        }

        void Bootstrap() {
            log_B(TAG::STA, "States::ChatState::Bootstrap", "");

            AuthState::Register("UsersState", State::Auth);

            assert(!usersSocket);
            usersSocket = new Socket( "users-stream", ResponseSuccess, ResponseError);

        }

        void Destroy() {
            log_B(TAG::STA, "States::ChatState::Destroy", "");

            assert(usersSocket);
            delete usersSocket;
                   usersSocket = 0;
        
        }

        const std::string& getSerializedList() {
            return usersResponse.usersList;    
        }
        
        inline void Init(const std::string& AUTH) {
            log_B(TAG::STA, "States::ChatState::Init", AUTH);

            assert(!pending);
            pending = true;
        
            UsersSocket::Request users_request;
                    users_request.type = UsersSocket::SIGNAL::OPEN;

                
            BaseRequest socket_data;
                socket_data.content = users_request.serialize();
                socket_data.AUTH = AUTH;

                usersSocket->setBuffer(socket_data);
             
        }

        inline void Close() {
            log_B(TAG::STA, "States::ChatState::Close", "");

            assert(pending);
            UsersSocket::Request users_request;
                    users_request.type = UsersSocket::SIGNAL::CLOSE;

            
            BaseRequest socket_data;
                socket_data.content = users_request.serialize();

            // stop computing next
            usersSocket->setBuffer(socket_data);
            pending = false;

        }

        inline void Notify(){

            log_B(TAG::STA, "States::ChatState::Notify", "State changes");

            for (const auto& subscription : subscribed) {
                log_C(TAG::STA, "States::ChatState::Notify", subscription.first);
                (*subscription.second)(); 
            }
            
        }

        inline void ResponseSuccess(const std::string str_response) {
            log_C(TAG::STA, "States::AuthState::Response", str_response);

            usersResponse = UsersSocket::Response(str_response);

            Notify();
        }

        inline void ResponseError(const std::string str_error) {
            
            usersResponse = UsersSocket::Response();

            Notify();
        }
        
        

        namespace State {

            void Auth() {

                const AuthSocket::SIGNAL 
                                auth_action = AuthState::getAuthAction();
                const User      auth_user   = AuthState::getAuthUser();

                switch(auth_action) {

                    case AuthSocket::SIGNAL::LOGIN:

                        if(auth_user.is_valid())
                            Init(auth_user._id);

                        break;

                    default:

                        Close();
                        break;
                    
                }
                
            }
        }
    }
}