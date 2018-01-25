#ifndef STATES_AUTH_STATE_DEFINITIONS_USER_H
#define STATES_AUTH_STATE_DEFINITIONS_USER_H

#include <iostream>
#include <json.hpp>

namespace States {
    namespace AuthState {

        class User {
            private:
                void from_json(const nlohmann::json& j);

            public:
                std::string name;
                std::string image;
                std::string _id;

                User();
                User(const nlohmann::json& j);
                User(const std::string& serialized);

                nlohmann::json to_json();
                std::string serialize();
                
                bool is_valid();
        };
        
    }
}

#endif