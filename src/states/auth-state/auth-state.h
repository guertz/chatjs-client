#ifndef STATES_AUTH_STATE_AUTH_STATE_H
#define STATES_AUTH_STATE_AUTH_STATE_H

#include "definitions/types.h"
#include "models/user/user.h"
#include "definitions/request.h"
#include "definitions/response.h"

namespace States {
    namespace AuthState {

        void Bootstrap();
        void Destroy();

        typedef std::map<std::string, void(*)()> Subscribers;
        void Register(std::string abc, void (*)());

        void Login(const std::string& );
        void Logout();
        
        AUTHSIGNAL  getAuthAction();
        User        getAuthUser();
        std::string getAuthError();

    }
}

#endif