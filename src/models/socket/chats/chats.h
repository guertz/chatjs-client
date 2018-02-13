#ifndef MODELS_SOCKET_CHATS_CHATS_H
#define MODELS_SOCKET_CHATS_CHATS_H

#include <iostream>
#include <json.hpp>
#include "models/json-item.h"
#include "models/user/user.h"

/**
 * @brief Interfaccia modelli data Chats (Json, enums): SIGNAL, Request, Response.
 * @file chats.h
 */

namespace ChatsSocket {

    /** Enum identificativo del tipo di azione che si sta compiendo. */
    enum SIGNAL {
        CREATE  = 0, /**< Enum per azione di creazione chat */
        CONNECT = 1, /**< Enum per azione di join user list */  
        ALL     = 2  /**< Enum per caso generale, solitamente errore */
    };

    /** Metodo per trasformare il valore string passato dal server in enum SIGNAL */
    SIGNAL str_to_enum(const std::string& chats_action);

    /** Metodo per trasformare il valore enum SIGNAL passato in string */
    std::string enum_to_str(const SIGNAL chats_signal);

    /** Interfaccia classe Request (Json)  */
    class Request : public JsonItem {
        
        public:
            SIGNAL  type; /**< Identificativo azione da eseguire sul server. */
            std::string destination; /**< Chiave identificativa utente di destinazione per nuova chat */

            Request();

            Request(const nlohmann::json& j); /**< Costruttore da oggetto json */
            Request(const std::string& serialized); /**< Costruttore da oggetto Json serializzato (string) */
            ~Request();

            nlohmann::json to_json() const;

    };

    /** Interfaccia classe Response (Json)  */
    class Response : public JsonItem {

        public:
            SIGNAL  type; /**< Identificativo azione da risposta del server. */
            std::string reference; /** Codice identificativo chat */
            User destination; /**< Utente di destinazione */
            User from; /**< Utente da cui arriva il messaggio */
            std::string creator; /**< Identificativo utente che ha creato la chat */            
            std::string error; /**< Campo che riporta gli errori verificatasi. */
            
            Response();
            Response(const nlohmann::json& j); /**< Costruttore da oggetto json */
            Response(const std::string& serialized); /**< Costruttore da oggetto Json serializzato (string) */
            ~Response();

            nlohmann::json to_json() const;
            
    };

}
#endif