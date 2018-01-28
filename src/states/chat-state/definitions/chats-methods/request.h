#ifndef STATES_CHAT_STATE_DEFINITIONS_CHATSMETHODS_REQUEST_H
#define STATES_CHAT_STATE_DEFINITIONS_CHATSMETHODS_REQUEST_H

#include <iostream>
#include <json.hpp>

#include "models/json-item.h"
#include "types.h"

namespace States {

    namespace ChatState {

        namespace ChatsMethods {

            namespace Request {

                class Chats : public JsonItem {

                    public:
                        TYPE  type;
                        std::string destination;

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