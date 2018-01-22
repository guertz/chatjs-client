
#include <iostream>
#include <json.hpp>
#include "user.h"

using namespace std;
using nlohmann::json;

namespace States {
    namespace AuthState {


        enum AUTHSIGNAL {
            LOGOUT = 0,
            LOGIN = 1            
        };

        namespace AuthActionDefinition {
            typedef struct AuthAction {
                string type;
                string user;
            } AuthAction;

            void to_json(json& j, const AuthAction& aa);

            void from_json(const json& j, AuthAction& aa);

        }

        namespace AuthBaseDefinition {
            typedef struct AuthBase {
                AUTHSIGNAL action;
                bool online;
            } AuthBase;

            void to_json(json& j, const AuthBase& ab);

            void from_json(const json& j, AuthBase& ab);

        }

        namespace AuthUserDefinition {
            // optimize?
            typedef struct AuthUser : AuthBaseDefinition::AuthBase, UserDefinition::User {

            } AuthUser;

            void to_json(json& j, const AuthUser& au);
            void from_json(const json& j, AuthUser& au);

        }
    }
}