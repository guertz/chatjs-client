#include <iostream>
#include <json.hpp>

using nlohmann::json;
using namespace std;

namespace States {
    namespace AuthState {
        namespace UserDefinition {

            typedef struct User {
                string name = "";
                string image = "";
                string _id = "";
            } User;

            void to_json(json& j, const User& u);

            void from_json(const json& j, User& u);

        }
    }
}