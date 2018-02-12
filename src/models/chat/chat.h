#ifndef MODELS_CHAT_CHAT_H
#define MODELS_CHAT_CHAT_H

#include <iostream>
#include <json.hpp>
#include <map>

#include "models/json-item.h"
#include "models/user/user.h"
#include "models/chat/message.h"


class Chat : public JsonItem{
    
    public:
        std::string reference;
        User destination;
        User from;
        std::string creator;
        Messages messages;

        Chat();
        Chat(const nlohmann::json& j);
        Chat(const std::string& serialized);

        ~Chat();

        nlohmann::json to_json() const;

        
};

typedef std::map<std::string,Chat> Chats;

class ChatsWrapper {
    public:
        static void json_to_chats(const nlohmann::json& j, Chats& c_map);
        static void chats_to_json(const Chats& c, nlohmann::json& j_map);
};


#endif