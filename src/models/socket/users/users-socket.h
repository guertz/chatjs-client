#ifndef MODELS_SOCKET_USERS_USERS_H
#define MODELS_SOCKET_USERS_USERS_H

#include <iostream>
#include <json.hpp>
#include "models/json-item.h"
#include "models/user/user.h"

/**
 * @brief Interfaccia modelli data UsersSocket (Json, enums): UsersSocket::SIGNAL, UsersSocket::UsersRequest, UsersSocket::UsersResponse.
 * @file users-socket.h
 */

namespace UsersSocket {
    
    /** Enum identificativo del tipo di azione che si sta compiendo. */
    enum SIGNAL {
        CLOSE = 0, /**< Enum per azione di chiusura stream */
        OPEN  = 1, /**< Enum per azione di apertura stream */  
        ALL   = 2  /**< Enum per caso generale, solitamente errore */
    };

    /** Metodo per trasformare il valore string passato dal server in enum UsersSocket::SIGNAL */
    SIGNAL str_to_enum(const std::string& users_action);

    /** Metodo per trasformare il valore enum UsersSocket::SIGNAL passato in string */
    std::string enum_to_str(const SIGNAL users_signal);

    /** Interfaccia classe UsersSocket::UsersRequest (Json)  */
    class UsersRequest : public JsonItem {
        
        public:
            SIGNAL type; /**< Identificativo azione da eseguire sul server. */

            UsersRequest();
            UsersRequest(const nlohmann::json& j);
            UsersRequest(const std::string& serialized);
            ~UsersRequest();

            nlohmann::json to_json() const;

    };

    /** Interfaccia classe UsersSocket::UsersResponse (Json)  */
    class UsersResponse : public JsonItem {

        public:
            SIGNAL type; /**< Identificativo azione da risposta del server. */
            std::string usersList; /**< Lista utenti json serializzato */
            std::string error; /**< Campo che riporta gli errori verificatasi. */
            
            UsersResponse();
            UsersResponse(const nlohmann::json& j);
            UsersResponse(const std::string& serialized);
            ~UsersResponse();

            nlohmann::json to_json() const;
            
    };

}
#endif