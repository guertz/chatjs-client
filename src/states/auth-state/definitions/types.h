#ifndef STATES_AUTH_STATE_DEFINITIONS_TYPES_H
#define STATES_AUTH_STATE_DEFINITIONS_TYPES_H

#include<iostream>

namespace States {
    namespace AuthState {

        // Corrispond to type on server
        // unify action && type keyword on server
        enum AUTHSIGNAL {
            LOGOUT = 0,
            LOGIN = 1 ,
            ALL = 2  // Refactor, remove all        
        };

        AUTHSIGNAL str_to_enum(const std::string& AUTH_ACTION);
        std::string enum_to_str(const AUTHSIGNAL AUTH_ACTION);

    }
}

#endif