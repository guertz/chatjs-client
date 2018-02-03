#ifndef STATES_AUTH_STATE_DEFINITIONS_REQUEST_H
#define STATES_AUTH_STATE_DEFINITIONS_REQUEST_H

#include <iostream>
#include <json.hpp>
#include "types.h"

#include "models/json-item.h"

namespace States {
    namespace AuthState {

        namespace Request {
            
            class Auth : public JsonItem {
                
                public:
                    AUTHSIGNAL  type;
                    std::string user; //  TODO: change to _id (since it is auth_key)

                    Auth();
                    Auth(const nlohmann::json& j);
                    Auth(const std::string& serialized);

                    nlohmann::json to_json() const;

            };

        }

    }
}

#endif