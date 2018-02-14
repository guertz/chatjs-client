#ifndef MODELS_CHAT_CHAT_H
#define MODELS_CHAT_CHAT_H

#include <iostream>
#include <json.hpp>
#include <map>

#include "models/json-item.h"
#include "models/user/user.h"
#include "models/chats/message.h"

/**
 * @brief Interfaccia data models per chat(s) (Json) 
 * @file chats.h
 */

/** Interfaccia classe Chat (JSON) */
class Chat : public JsonItem{
    
    public:
        std::string reference; /**< Codice identificativo della chat di riferimento */
        User destination; /**< Utente di destinazione dei messaggi */
        User from; /**< Utente che invia i messaggi */
        std::string creator; /**< Codice utente che ha iniziato la chat */
        Messages messages; /**< Elenco di messaggi */

        Chat();
        Chat(const nlohmann::json& j);
        Chat(const std::string& serialized);

        ~Chat();

        nlohmann::json to_json() const;

        
};
/**  Chats, stl container map di oggetti di tipo Chat (chat) */
typedef std::map<std::string,Chat> Chats;

/** Interfaccia wrapper per serializzare/deserializzare oggetti Chats dal formato json e non */
class ChatsWrapper {
    public:
        /** Metodo che ritorna elenco di chats (map Chat) da oggetto json */
        static Chats json_to_chats(const nlohmann::json& j);

        /** Metodo che ritorna elenco di chats json da oggetto chats (map Chats) */
        static nlohmann::json chats_to_json(const Chats& c);
};


#endif