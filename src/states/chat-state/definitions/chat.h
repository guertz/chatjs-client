#ifndef STATES_CHAT_STATE_DEFINITIONS_CHAT_H
#define STATES_CHAT_STATE_DEFINITIONS_CHAT_H

#include <iostream>
#include <json.hpp>
#include <map>
#include "message.h"
#include "models/json-item.h"
#include "models/user/user.h"

namespace States {
    namespace ChatState {

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

                nlohmann::json to_json() const;

               
        };

        typedef std::map<std::string,Chat> Chats;
    }
}


#endif