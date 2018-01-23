#include <iostream>
#include <json.hpp>

#include "auth.h"

#include "common/helpers/helpers.h"

using namespace Helpers::safestr;
using nlohmann::json;
using namespace std;

namespace States {
    namespace AuthState {

        namespace AuthActionDefinition {

            void to_json(json& j, const AuthAction& aa) {
                j = json{
                        { "type", aa.type }, 
                        { "user", aa.user }
                    };
            }

            void from_json(const json& j, AuthAction& aa) {
                aa.type = j.at("type").get<string>();
                aa.user = j.at("user").get<string>();
            }

        }

        namespace AuthBaseDefinition {

            // Default initializer for user
            //      Even from response if error
            //      With serialized string no problem

            // if !user load default
            void to_json(json& j, const AuthBase& ab) {
                j = json{
                        { "action", ab.action}, 
                        { "online", ab.online},
                        { "user", ab.user } // json auto translate?
                    };
            }

            void from_json(const json& j, AuthBase& ab) {
                ab.action = j.at("action").get<AUTHSIGNAL>();
                ab.online = j.at("online").get<bool>();
                ab.user   = j.at("user");
            }

        }
    }
}