#ifndef MODELS_SOCKET_AUTH_AUTH_H
#define MODELS_SOCKET_AUTH_AUTH_H

#include <iostream>
#include <json.hpp>
#include "models/json-item.h"
#include "models/user/user.h"

/**
 * @brief Interfaccia modelli data AuthSocket (Json, enums): AuthSocket::SIGNAL, AuthSocket::AuthRequest, AuthSocket::AuthResponse.
 * @file auth-socket.h
 */

namespace AuthSocket {

    /** Enum identificativo del tipo di azione che si sta compiendo. */
    enum SIGNAL {
        LOGOUT = 0, /**< Enum per azione di logout */
        LOGIN  = 1, /**< Enum per azione di login */  
        ALL    = 2  /**< Enum per caso generale, solitamente errore */
    };

    /** Metodo per trasformare il valore string passato dal server in enum AuthSocket::SIGNAL */
    SIGNAL str_to_enum(const std::string& auth_action);

    /** Metodo per trasformare il valore enum AuthSocket::SIGNAL passato in string */
    std::string enum_to_str(const SIGNAL auth_signal);

    /** Interfaccia classe AuthSocket::AuthRequest (Json)  */
    class AuthRequest : public JsonItem {
        
        public:
            SIGNAL  type; /**< Identificativo azione da eseguire sul server. */
            std::string user; /**< Chiave identificativa utente per effettuare login (User ID) */

            /**
            * Costruttore di default. Inizializza la classe con
            * chiave utente vuota e azione logout
            */
            AuthRequest(); 

            AuthRequest(const nlohmann::json& j);
            AuthRequest(const std::string& serialized);
            ~AuthRequest();

            nlohmann::json to_json() const;

    };

    /** Interfaccia classe AuthSocket::AuthResponse (Json)  */
    class AuthResponse : public JsonItem {

        public:
            SIGNAL type; /**< Identificativo azione da risposta del server. */
            User user; /**< Contenuto utente. valori di default se autenticazione fallisce. */
            bool online; /**< Campo che specifica se l'azione di login è andata a buon file. */
            
            std::string error; /**< Campo che riporta gli errori verificatasi. */
            
            /**
            * Costruttore di default. Inizializza la classe con
            * logout, utente default, false e stringa vuota errori
            */
            AuthResponse();
            AuthResponse(const nlohmann::json& j); 
            AuthResponse(const std::string& serialized);
            ~AuthResponse();

            nlohmann::json to_json() const;
            
    };

}
#endif