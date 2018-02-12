#ifndef MODELS_SOCKET_AUTH_AUTH_H
#define MODELS_SOCKET_AUTH_AUTH_H

#include <iostream>
#include <json.hpp>
#include "models/json-item.h"
#include "models/user/user.h"

/**
 * @brief Interfaccia modelli data Auth (Json, enums): SIGNAL, Request, Response.
 * @file auth.h
 */

namespace AuthSocket {

    /** Enum identificativo del tipo di azione che si sta compiendo. */
    enum SIGNAL {
        LOGOUT = 0, /**< Enum per azione di logout */
        LOGIN  = 1, /**< Enum per azione di login */  
        ALL    = 2  /**< Enum per caso generale, solitamente errore */
    };

    /** Metodo per trasformare il valore string passato dal server in enum SIGNAL */
    SIGNAL str_to_enum(const std::string& auth_action);

    /** Metodo per trasformare il valore enum SIGNAL passato in string */
    std::string enum_to_str(const SIGNAL auth_signal);

    /** Interfaccia classe Request (Json)  */
    class Request : public JsonItem {
        
        public:
            SIGNAL  type; /**< Identificativo azione da eseguire sul server. */
            std::string user; /**< Chiave identificativa utente per effettuare login (User ID) */
                //  TODO: change to _id (since it is auth_key)

        /**
            * Costruttore di default. Inizializza la classe con
            * chiave utente vuota e azione logout
            */
            Request(); 

            Request(const nlohmann::json& j); /**< Costruttore da oggetto json */
            Request(const std::string& serialized); /**< Costruttore da oggetto Json serializzato (string) */
            ~Request();

            nlohmann::json to_json() const;

    };

    /** Interfaccia classe Response (Json)  */
    class Response : public JsonItem {

        public:
            SIGNAL type; /**< Identificativo azione da risposta del server. */
            User user; /**< Contenuto utente. valori di default se autenticazione fallisce. */
            bool online; /**< Campo che specifica se l'azione di login è andata a buon file. */
            
            std::string error; /**< Campo che riporta gli errori verificatasi. */
            
        /**
            * Costruttore di default. Inizializza la classe con
            * logout, utente default, false e stringa vuota errori
            */
            Response();
            Response(const nlohmann::json& j); /**< Costruttore da oggetto json */
            Response(const std::string& serialized); /**< Costruttore da oggetto Json serializzato (string) */
            ~Response();

            nlohmann::json to_json() const;
            
    };

}
#endif