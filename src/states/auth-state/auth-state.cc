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

        // Dichiarazione metodi non definiti a livello di interfaccia

        /**
         * Metodo per gestire l'avvenuta ricezione nel corretto formato
         * a seguito di un azione di tipo AUTHSIGNAL sul canale di comunicazione
         * socket authSocket.
         *
         * @param str_response Messaggio di risposta in formato JSON serializzato
         */
        inline void ResponseSuccess(const std::string str_response);

        /**
         * Metodo per gestire l'avvenuta ricezione di un messaggio di errore a 
         * seguito di un azione di tipo AUTHSIGNAL sul canale di comunicazione
         * socket authSocket.
         *
         * @param str_error Messaggio di errore stringa testo
         */
        inline void ResponseError(const std::string str_error);

        /** 
         * Metodo per notificare cambiamenti di stato ai componenti che
         * hanno sottoscritto allo stato di autenticazione
         */
        inline void Notify();

        // Variabile che contiene il puntatore al canale di comunicazione 
        // websocket all'endpoint 'auth' e ha durata di vita per tutto il
        // corso del programma
        static Socket* authSocket = 0;

        // Variabile per specificare se vi sono azioni in attesa di risposta
        // in corso
        static bool pending = false;
        
        // Variabile in cui viene mantenuto il contenuto a seguito di una risposta
        // da parte del canale di comunicazione authSocket
        static AuthResponse authResponse;

        // Mappa dei componenti che sottoscrivono ad eventi relativi allo stato
        // di autenticazione
        static Subscribers subscribed;

        void Register(std::string cb_name, void (*cb_fn)()) {
            log_C(TAG::STA, "States::AuthState::Register", cb_name);

            subscribed[cb_name] = cb_fn;
        }

        void Bootstrap() {
            log_B(TAG::STA, "States::AuthState::Bootstrap", "");

            assert(!authSocket);
            authSocket = new Socket("auth", ResponseSuccess, ResponseError);

        }

        void Destroy() {
            log_B(TAG::STA, "States::AuthState::Destroy", "");

            assert(authSocket);
            delete authSocket;
                   authSocket = 0;
        }

        void Login(const std::string& AUTH_KEY){
            log_C(TAG::STA, "States::AuthState::Login", AUTH_KEY);

            assert(!pending && !authResponse.online);
            // if(!pending && !authResponse.online){
            pending = true;
            
            AuthRequest auth_request;
                auth_request.type = SIGNAL::LOGIN;
                auth_request.user = AUTH_KEY;


            BaseRequest socket_data;
                        socket_data.content = auth_request.serialize();

            authSocket->setBuffer(socket_data);
            // }

        }

        void Logout(){
            log_C(TAG::STA, "States::AuthState::Logout", "");

            assert(!pending && authResponse.online);
            // if(!pending && authResponse.online){
            pending = true;


            AuthRequest auth_request;
                auth_request.type = SIGNAL::LOGOUT;
                // auth_request.user = "";

            
            BaseRequest socket_data;
                        socket_data.content = auth_request.serialize();
                        socket_data.AUTH    = authResponse.user._id;

            authSocket->setBuffer(socket_data);
            // }

        }

        SIGNAL getAuthAction() {
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

        inline void ResponseSuccess(const std::string str_response) {
            log_C(TAG::STA, "States::AuthState::Response", str_response);

            authResponse = AuthResponse(str_response);
            pending = false;

            Notify();
        }

        inline void ResponseError(const std::string str_error) {
            log_C(TAG::STA, "States::AuthState::Response", str_error);

            AuthResponse response_errors;
                         // Other action won't send errors
                         response_errors.type  = SIGNAL::LOGIN; 
                         response_errors.error = str_error;

            authResponse = response_errors;
            pending = false;

            Notify();
        }

    }
}