#ifndef STATES_CHAT_STATE_DEFINITIONS_CHATMETHODS_REQUEST_H
#define STATES_CHAT_STATE_DEFINITIONS_CHATMETHODS_REQUEST_H

#include <iostream>
#include <json.hpp>

#include "models/json-item.h"
#include "types.h"

namespace States {

    namespace ChatState {


        namespace ChatMethods {

            namespace Request {

                class Chat : public JsonItem {

                    public:
                        TYPE  type;
                        std::string text;

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