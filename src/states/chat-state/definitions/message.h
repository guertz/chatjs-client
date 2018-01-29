#ifndef STATES_CHAT_STATE_DEFINITIONS_MESSAGE_H
#define STATES_CHAT_STATE_DEFINITIONS_MESSAGE_H

#include <iostream>
#include <json.hpp>
#include <vector>

#include "models/json-item.h"
#include "models/user/user.h"

namespace States {
    namespace ChatState {

        class Message : public JsonItem{

            public:
                std::string text;
                bool isMe; // _is_me
                User avatar; // isn't it the user definition itself
                std::string time;

                Message();
                Message(const nlohmann::json& j);
                Message(const std::string& serialized);

                nlohmann::json to_json() const;
        };

        typedef std::vector<Message> Messages;

        class MessagesWrapper {
            public:
                static void json_to_messages(const nlohmann::json& j, Messages& m_vect);
                static void messages_to_json(const Messages& m, nlohmann::json& j_vect);
        };

    }
}


#endif