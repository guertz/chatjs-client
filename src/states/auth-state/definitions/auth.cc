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

            void to_json(json& j, const AuthBase& ab) {
                j = json{
                        { "action", ab.action}, 
                        { "online", ab.online}
                    };
            }

            void from_json(const json& j, AuthBase& ab) {
                ab.action = j.at("action").get<AUTHSIGNAL>();
                ab.online = j.at("online").get<bool>();
            }

        }

        namespace AuthUserDefinition {

            // ERROR PRONE, REDUNDANT
            void to_json(json& j, const AuthUser& au) {
                j = json{
                        { "action", au.action}, 
                        { "online", au.online},
                        { "name", au.name}, 
                        { "image", au.image}, 
                        { "_id", au._id}
                    };
            }

            void from_json(const json& j, AuthUser& au) {
                au.action = j.at("action").get<AUTHSIGNAL>();
                au.online = j.at("online").get<bool>();
                au.name = j.at("name").get<string>();
                au.image = j.at("image").get<string>();
                au._id = j.at("_id").get<string>();
            }
        }
    }
}