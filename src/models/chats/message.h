#ifndef MODELS_CHAT_MESSAGE_H
#define MODELS_CHAT_MESSAGE_H

#include <iostream>
#include <json.hpp>
#include <vector>

#include "models/json-item.h"
#include "models/user/user.h"

/**
 * @brief Interfaccia data models per messaggio/i (Json) 
 * @file message.h
 */

/** Interfaccia classe messaggio (JSON) */
class Message : public JsonItem{

    public:
        std::string text; /**< Testo contenuto del messaggio */
        bool isMe; /**< Valore che definisce se il messaggio è stato mandato da me */
        User avatar; /** Utente di riferimento del messaggio */
        std::string time; /** Momento in cui è stato percepito il messaggio dal server */

        Message();
        Message(const nlohmann::json& j);
        Message(const std::string& serialized);
        ~Message();

        nlohmann::json to_json() const;
};

/** 
 * Messaggi, stl container vector di oggetti di tipo Message (messaggio). 
 * Vi vengono inseriti i messaggi tramite push
 */
typedef std::vector<Message> Messages;

/** Interfaccia wrapper per serializzare/deserializzare oggetti Messages dal formato json e non */
class MessagesWrapper {
    public:
        /** Metodo che ritorna elenco di messaggi vector Messages da oggetto json */
        static Messages json_to_messages(const nlohmann::json& j);

        /** Metodo che ritorna elenco di messaggi json da oggetto vector Messages */
        static nlohmann::json messages_to_json(const Messages& m);
};


#endif