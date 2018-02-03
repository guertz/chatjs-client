#ifndef STATES_USERS_STATE_DEFINITIONS_RESPONSE_H
#define STATES_USERS_STATE_DEFINITIONS_RESPONSE_H

#include <iostream>
#include <json.hpp>
#include "types.h"

#include "models/json-item.h"

namespace States {
    namespace UsersState {
        namespace Response {

            class Stream : public JsonItem{

                public:
                    STREAMSIGNAL type;
                    std::string  usersList;

                    Stream();
                    Stream(const nlohmann::json& j);
                    Stream(const std::string& serialized);

                    nlohmann::json to_json() const;
                    
            };

        }
    }
}

#endif