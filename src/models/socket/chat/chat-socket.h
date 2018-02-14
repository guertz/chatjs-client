#ifndef MODELS_SOCKET_CHAT_CHAT_H
#define MODELS_SOCKET_CHAT_CHAT_H

#include <iostream>
#include <json.hpp>
#include "models/json-item.h"
#include "models/user/user.h"

/**
 * @brief Interfaccia modelli data ChatSocket (Json, enums): ChatSocket::SIGNAL, ChatSocket::ChatRequest, ChatSocket::ChatResponse.
 * @file chat-socket.h
 */

namespace ChatSocket {

    /** Enum identificativo dell'azione che si sta compiendo */
    enum SIGNAL {
        JOIN    = 0, /**< Enum per azione di partecipazione a una chat esistente */
        SEND    = 1, /**< Enum per azione di invio di messaggio */
        ALL     = 2 /**< Enum per caso generale, solitamente errore */
    };

    /** Metodo per trasformare il valore string passato dal server in enum ChatSocket::SIGNAL */
    SIGNAL str_to_enum(const std::string& chat_action);

    /** Metodo per trasformare il valore enum ChatSocket::SIGNAL passato in string */
    std::string enum_to_str(const SIGNAL  chat_signal);

    /** Interfaccia classe ChatSocket::ChatRequest (Json)  */
    class ChatRequest : public JsonItem {

        public:
            SIGNAL  type;  /**< Identificativo azione da eseguire sul server. */
            std::string text; /**< Contenuto testo del messaggio */

            ChatRequest();
            ChatRequest(const nlohmann::json& j);
            ChatRequest(const std::string& serialized);
            ~ChatRequest();

            nlohmann::json to_json() const;

    };

    /** Interfaccia classe ChatSocket::ChatResponse (Json)  */
    class ChatResponse : public JsonItem {

        public:
            SIGNAL  type; /**< Identificativo azione compiuta */
            std::string ref; /**< Identificativo chat di riferimento */
            std::string text; /**< Contenuto del messaggio di testo */
            std::string time; /**< Momento in cui è stato percepito il messaggio dal server */
            bool isMe; /**< Valore che definisce se il messaggio è stato mandato da me */
            User avatar; /**< Utente di riferimento del messaggio */

            ChatResponse();
            ChatResponse(const nlohmann::json& j);
            ChatResponse(const std::string& serialized);
            ~ChatResponse();

            nlohmann::json to_json() const;

    };
}


#endif