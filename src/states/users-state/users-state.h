#ifndef STATES_USERS_STATE_USERS_STATE_H
#define STATES_USERS_STATE_USERS_STATE_H

#include "definitions/stream.h"
#include "definitions/request.h"
#include "definitions/response.h"

namespace States {
    namespace UsersState {

        typedef std::map<std::string, void(*)()> Subscribers;

        void Register(std::string abc, void (*)());

        void Bootstrap();
        void Destroy();
    
        const std::string& getSerializedList();

        namespace Sockets {
            namespace UsersStream {
                // Better ways?
                inline void Init(const std::string& );
                inline void Close();
                inline void ResponseSuccess(const std::string str_response);
                inline void ResponseError(const std::string str_error);
            }
        }

        namespace State {
            void Auth();
        }
    }
}

#endif