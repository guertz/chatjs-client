#include <iostream>
#include "auth-state.h"
#include "protocol/sockets/wscustom.h"
#include "common/helpers/helpers.h"
#include <json.hpp>

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
        static char* cached       = 0;

        static Subscribers subscribed;

        void notify(const char* args){
            
            safeptr::free_block(cached);
            cached = safestr::duplicate(args);

            for (const auto& item : subscribed) {
                
                (*item.second)(safestr::duplicate(args));
            }

            safeptr::free_block(args);

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
            

            json report = auth_data;
            notify(safestr::duplicate(report.dump().c_str()));

            pending = false;
        }

        void LoginResponseError(const string error) {

            UserDefinition::User default_user;

            AuthBaseDefinition::AuthBase auth_data {
                AUTHSIGNAL::LOGIN,
                false,
                default_user
            };

            json report = auth_data;
            notify(safestr::duplicate(report.dump().c_str()));

            pending = false;
        }

        const char* getAuthStatus(){
            return cached ? safestr::duplicate(cached) : 0;
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


        void Register(string abc, void (*fn)(const char* arg)){
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
            
            json report = auth_base;

            notify(safestr::duplicate(report.dump().c_str()));

        }


    }
}