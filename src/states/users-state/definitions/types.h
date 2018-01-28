#ifndef STATES_USERS_STATE_DEFINITIONS_TYPES_H
#define STATES_USERS_STATE_DEFINITIONS_TYPES_H

#include <iostream>

namespace States {
    namespace UsersState {

        enum STREAMSIGNAL {
            CLOSE = 0,
            OPEN = 1
        };

        STREAMSIGNAL str_to_enum(const std::string& STREAM_ACTION);
        std::string enum_to_str(const STREAMSIGNAL STREAM_ACTION);

    }
}

#endif