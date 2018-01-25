#ifndef STATES_AUTH_STATE_DEFINITIONS_AUTH_H
#define STATES_AUTH_STATE_DEFINITIONS_AUTH_H

#include <json.hpp>
#include "user.h"

namespace States {
    namespace AuthState {


        enum AUTHSIGNAL {
            LOGOUT = 0,
            LOGIN = 1 ,
            ALL = 2           
        };

        namespace AuthActionDefinition {
            typedef struct AuthAction {
                std::string type;
                std::string user;
            } AuthAction;

            void to_json(nlohmann::json& j, const AuthAction& aa);

            void from_json(const nlohmann::json& j, AuthAction& aa);

        }

        namespace AuthBaseDefinition {
            typedef struct AuthBase {
                AUTHSIGNAL action;
                bool online;
                UserDefinition::User user;
            } AuthBase;

            void to_json(nlohmann::json& j, const AuthBase& ab);

            void from_json(const nlohmann::json& j, AuthBase& ab);

        }

    }
}

#endif