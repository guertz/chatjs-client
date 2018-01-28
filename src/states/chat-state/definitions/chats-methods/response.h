#ifndef STATES_CHAT_STATE_DEFINITIONS_CHATSMETHODS_RESPONSE_H
#define STATES_CHAT_STATE_DEFINITIONS_CHATSMETHODS_RESPONSE_H

#include <iostream>
#include <json.hpp>

#include "models/json-item.h"
#include "types.h"
#include "models/user/user.h"

namespace States {

    namespace ChatState {

        namespace ChatsMethods {

            namespace Response {

                class Chats : public JsonItem {

                    public:
                        TYPE  type;
                        std::string reference;
                        User destination;
                        User from;
                        std::string creator;

                        Chats();
                        Chats(const nlohmann::json& j);
                        Chats(const std::string& serialized);

                        nlohmann::json to_json() const;

                };
        
            }
        }
        
    }
}

#endif