#include<iostream>
#include <map>

#include "definitions/auth.h"

using namespace std;

namespace States {
    namespace AuthState {

        typedef map<string, void(*)(const char* arg)> Subscribers;

        void Register(string abc, void (*fn)(const char* arg));

        void Logout();
        void Login(AuthActionDefinition::AuthAction& );
        void Bootstrap();
        const char* getAuthStatus();

    }
}