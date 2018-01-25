#ifndef STATES_AUTH_STATE_DEFINITIONS_RESPONSE_H
#define STATES_AUTH_STATE_DEFINITIONS_RESPONSE_H

#include <iostream>
#include <json.hpp>
#include "user.h"
#include "auth.h"

namespace States {
    namespace AuthState {
        namespace Response {

            // String serializator and deserializator
            // Virtual Methods
            class Auth {
                private:
                    void from_json(const nlohmann::json& j);

                public:
                    AUTHSIGNAL type;
                    User user;
                    bool online;

                    Auth(); // used for general case of errors
                    Auth(const nlohmann::json& j);
                    Auth(const std::string& serialized);

                    nlohmann::json to_json();
                    std::string serialize();
                    
            };

            // private attributes?
            // specifying action type
            // class Login  : Auth  {};
            // class Logout : Auth  {};

        }
    }
}

#endif