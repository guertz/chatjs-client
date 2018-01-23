#include "definitions/auth.h"

namespace States {
    namespace AuthState {

        typedef std::map<std::string, void(*)(const AuthBaseDefinition::AuthBase& )> Subscribers;

        void Register(std::string abc, void (*fn)(const AuthBaseDefinition::AuthBase& ));

        void Logout();
        void Login(AuthActionDefinition::AuthAction& );
        void Bootstrap();
        const UserDefinition::User& getAuthUser();

    }
}