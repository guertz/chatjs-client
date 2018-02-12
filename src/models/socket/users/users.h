#ifndef MODELS_SOCKET_USERS_USERS_H
#define MODELS_SOCKET_USERS_USERS_H

#include <iostream>
#include <json.hpp>
#include "models/json-item.h"
#include "models/user/user.h"

/**
 * @brief Interfaccia modelli data Users (Json, enums): SIGNAL, Request, Response.
 * @file users.h
 */

namespace UsersSocket {
    
    /** Enum identificativo del tipo di azione che si sta compiendo. */
    enum SIGNAL {
        CLOSE = 0, /**< Enum per azione di chiusura stream */
        OPEN  = 1, /**< Enum per azione di apertura stream */  
        ALL   = 2  /**< Enum per caso generale, solitamente errore */
    };

    /** Metodo per trasformare il valore string passato dal server in enum SIGNAL */
    SIGNAL str_to_enum(const std::string& users_action);

    /** Metodo per trasformare il valore enum SIGNAL passato in string */
    std::string enum_to_str(const SIGNAL users_signal);

    /** Interfaccia classe Request (Json)  */
    class Request : public JsonItem {
        
        public:
            SIGNAL type; /**< Identificativo azione da eseguire sul server. */

            Request(); /**< Costruttore default */

            Request(const nlohmann::json& j); /**< Costruttore da oggetto json */
            Request(const std::string& serialized); /**< Costruttore da oggetto Json serializzato (string) */
            ~Request();

            nlohmann::json to_json() const;

    };

    /** Interfaccia classe Response (Json)  */
    class Response : public JsonItem {

        public:
            SIGNAL type; /**< Identificativo azione da risposta del server. */
            std::string usersList; /**< Lista utenti json serializzato */
            std::string error; /**< Campo che riporta gli errori verificatasi. */
            
            Response(); /**< Costruttore default */
            Response(const nlohmann::json& j); /**< Costruttore da oggetto json */
            Response(const std::string& serialized); /**< Costruttore da oggetto Json serializzato (string) */
            ~Response();

            nlohmann::json to_json() const;
            
    };

}
#endif