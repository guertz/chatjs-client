#ifndef STATES_USERS_STATE_DEFINITIONS_REQUEST_H
#define STATES_USERS_STATE_DEFINITIONS_REQUEST_H

#include <iostream>
#include <json.hpp>
#include "stream.h"

namespace States {
    namespace UsersState {

        namespace Request {
            
            class Stream {
                private:
                    void from_json(const nlohmann::json& j);

                public:
                    STREAMSIGNAL  type;

                    Stream();
                    Stream(const nlohmann::json& j);
                    Stream(const std::string& serialized);

                    nlohmann::json to_json();
                    std::string serialize();

            };

        }

    }
}

#endif