#ifndef STATES_AUTH_STATE_DEFINITIONS_REQUEST_H
#define STATES_AUTH_STATE_DEFINITIONS_REQUEST_H

#include <iostream>
#include <json.hpp>
#include "auth.h"

namespace States {
    namespace AuthState {

        // All extends IJSON virtual con i metodi di base
        // Request e response poi espandono le apposite classi
        namespace Request {
            
            class Auth {
                private:
                    void from_json(const nlohmann::json& j);

                public:
                    AUTHSIGNAL  type;
                    std::string user; //  TODO: change to _id (since it is auth_key)

                    Auth(); // => useless
                    Auth(const nlohmann::json& j); // from_json
                    Auth(const std::string& serialized);  // deserialize

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