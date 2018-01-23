#ifndef STATES_AUTH_STATE_DEFINITIONS_USER_H
#define STATES_AUTH_STATE_DEFINITIONS_USER_H

#include <json.hpp>

namespace States {
    namespace AuthState {
        namespace UserDefinition {

            typedef struct User {
                std::string name = "";
                std::string image = "";
                std::string _id = "";
            } User;

            void to_json(nlohmann::json& j, const User& u);

            void from_json(const nlohmann::json& j, User& u);

            void setDefault(User& u);

        }
    }
}

#endif