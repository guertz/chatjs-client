#include <map>
#include "user.h"

using namespace std;
using namespace UserDefinition; 

#ifndef auth_state_definition_h
#define auth_state_definition_h

namespace AuthState{
    typedef map<string, void(*)(const char* arg)> auth_component_list;
    
    enum AUTHSIGNAL {
        LOGIN,
        LOGOUT
    };

    void Register(string abc, void (*fn)(const char* arg));
    // should return current status for components that joins later

    auth_component_list getComponentList();

    void logout();
    void Login(const char* userId);
    void Bootstrap();
    const char* getAuthStatus();

    struct AuthUser : User {
        string _id; // const
        bool online;
    };
}

#endif