#include "auth.h"

using namespace std;
namespace States {
    namespace AuthState{

        AUTHSIGNAL str_to_enum(const string& AUTH_ACTION){
            if(AUTH_ACTION.compare("login") == 0)
                return AUTHSIGNAL::LOGIN;
            if(AUTH_ACTION.compare("logout") == 0)
                return AUTHSIGNAL::LOGOUT;
            
            return AUTHSIGNAL::ALL;
        }

        string enum_to_str(const AUTHSIGNAL AUTH_ACTION){

            switch(AUTH_ACTION) {
                case AUTHSIGNAL::LOGIN: 
                    return "login";
                case AUTHSIGNAL::LOGOUT:
                    return "logout";
                default:
                    return "";
            }
        }

    }
}