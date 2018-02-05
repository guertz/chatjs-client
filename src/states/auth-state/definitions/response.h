#ifndef STATES_AUTH_STATE_DEFINITIONS_RESPONSE_H
#define STATES_AUTH_STATE_DEFINITIONS_RESPONSE_H

#include <iostream>
#include <json.hpp>
#include "models/user/user.h"
#include "types.h"

#include "models/json-item.h"

namespace States {
    namespace AuthState {
        namespace Response {

            class Auth : public JsonItem {

                public:
                    AUTHSIGNAL type;
                    User user;
                    bool online;
                    std::string error;
                    
                    Auth();
                    Auth(const nlohmann::json& j);
                    Auth(const std::string& serialized);

                    nlohmann::json to_json() const;
                    
            };

        }
    }
}

#endif