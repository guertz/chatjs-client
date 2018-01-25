#ifndef STATES_USERS_STATE_DEFINITIONS_AUTH_H
#define STATES_USERS_STATE_DEFINITIONS_AUTH_H

#include <iostream>

namespace States {
    namespace UsersState {

        // Corrispond to type on server
        // unify action && type keyword on server
        enum STREAMSIGNAL {
            CLOSE = 0,
            OPEN = 1
        };

        STREAMSIGNAL str_to_enum(const std::string& STREAM_ACTION);
        std::string enum_to_str(const STREAMSIGNAL STREAM_ACTION);

    }
}

#endif