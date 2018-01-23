#include <iostream>
#include <json.hpp>

#include "user.h"

using nlohmann::json;
using namespace std;

namespace States {
    namespace AuthState {
        namespace UserDefinition {

            void to_json(json& j, const User& u) {
                j = json{
                        { "name", u.name}, 
                        { "image", u.image}, 
                        { "_id", u._id}
                    };
            }

            void from_json(const json& j, User& u) {
                u.name = j.at("name").get<string>();
                u.image = j.at("image").get<string>();
                u._id = j.at("_id").get<string>();
            }

            void setDefault(User& u){
                u.name = "";
                u.image = "";
                u._id = "";
            }

        }
    }
}