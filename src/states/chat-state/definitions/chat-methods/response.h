#ifndef STATES_CHAT_STATE_DEFINITIONS_CHATMETHODS_RESPONSE_H
#define STATES_CHAT_STATE_DEFINITIONS_CHATMETHODS_RESPONSE_H

#include <iostream>
#include <json.hpp>

#include "models/json-item.h"
#include "types.h"
#include "models/user/user.h"

namespace States {

    namespace ChatState {

        namespace ChatMethods {

            namespace Response {
                class Chat : public JsonItem {

                    public:
                        TYPE  type;
                        std::string ref;
                        std::string text;
                        std::string time;
                        bool isMe;
                        User avatar;

                        Chat();
                        Chat(const nlohmann::json& j);
                        Chat(const std::string& serialized);

                        nlohmann::json to_json() const;

                };
            
            }
        }
        
    }
}

#endif