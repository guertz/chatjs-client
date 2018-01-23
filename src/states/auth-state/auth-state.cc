#include <iostream>
#include <map>
#include <json.hpp>

#include "auth-state.h"
#include "protocol/sockets/wscustom.h"

#include "common/helpers/helpers.h"
#include "common/logger/logger.h"

using json = nlohmann::json;
using namespace ws;
using namespace std;
using namespace Helpers;

namespace States {
    
    // static || inline (if not method interface)
    namespace AuthState {

        static Socket* authSocket = 0;
        static bool pending       = false;
        static bool loggedIn      = false;
        
        static UserDefinition::User authUser;

        static Subscribers subscribed;

        void notify(const AuthBaseDefinition::AuthBase& auth_data){
            
            authUser = auth_data.user;

            for (const auto& item : subscribed)
                (*item.second)(auth_data);
            

        }

        void LoginResponseSuccess(const string success) {

            json auth_response = json::parse(success);
            UserDefinition::User default_user;

            AuthBaseDefinition::AuthBase auth_data {
                AUTHSIGNAL::LOGIN,
                auth_response.at("online"),
                default_user
            };

            // alternative, server sends an error
            //              server sends empty dummy format
            if(auth_data.online)
                auth_data.user = auth_response.at("user");
            
            notify(auth_data);

            pending = false;
        }

        void LoginResponseError(const string error) {

            UserDefinition::User default_user;

            AuthBaseDefinition::AuthBase auth_data {
                AUTHSIGNAL::LOGIN,
                false,
                default_user
            };

            notify(auth_data);

            pending = false;
        }

        const UserDefinition::User& getAuthUser(){
            return authUser;
        }

        void Bootstrap() {
            
            try {
                authSocket = new Socket("users", LoginResponseSuccess, LoginResponseError);
            }catch(...) {
                log_base("AuthState::Socket>>'users'", "Exception reported");
            }

        }

        void Destroy() {
            if(authSocket){
                delete authSocket;
                       authSocket = 0;
            }
        }


        void Register(string abc, void (*fn)(const AuthBaseDefinition::AuthBase&)){
            subscribed[abc] = fn;
        }

        void Login(AuthActionDefinition::AuthAction& auth_action){
            if(!pending && !loggedIn){
                pending = true;
                
                // Changes on server
                //      1) request format
                //      2) reponse format
                //      3) auth request
                json json_auth = auth_action;

                RequestDefinition::Request auth_request = RequestDefinition::createEmpty();
                        auth_request.content = json_auth.dump();

                authSocket->setBuffer(auth_request);
            }

        }

        void Logout(){
            UserDefinition::User default_user;

            AuthBaseDefinition::AuthBase auth_base {
                AUTHSIGNAL::LOGOUT,
                false,
                default_user
            };

            notify(auth_base);

        }


    }
}