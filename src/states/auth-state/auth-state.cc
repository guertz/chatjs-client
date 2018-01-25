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

        void ResponseSuccess(const string auth_response) {

            AuthBaseDefinition::AuthBase auth_data = json::parse(auth_response);
            
            loggedIn = auth_data.online;
            pending = false;

            notify(auth_data);
        }

        // Doesnt mean user is chicked out (check on return exception)
        void ResponseError(const string error) {

            UserDefinition::User default_user;

            // Cannot cast because of content undefined
            AuthBaseDefinition::AuthBase auth_data {
                AUTHSIGNAL::ALL,
                false,
                default_user
            };

            loggedIn = false;
            pending = false;

            notify(auth_data);

            
        }

        const UserDefinition::User& getAuthUser(){
            return authUser;
        }

        void Bootstrap() {
            
            try {
                authSocket = new Socket("user", ResponseSuccess, ResponseError);
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

            // assert
            if(!pending && !loggedIn){
                pending = true;
                
                json json_auth = auth_action;

                RequestDefinition::Request auth_request = RequestDefinition::createEmpty();
                        auth_request.content = json_auth.dump();

                authSocket->setBuffer(auth_request);
            }

        }

        void Logout(){

            // TODO: prevent getAuth() to avoid inconsistent state
            //       component will only be able to get authenticated user
            //       by watching & handling changes from the provider stream

            // TODO: is it better to not use Sockets in component but only 
            //       in providers?

            // TODO: is it better to send AUTH header all the time or on 
            //       the first message (init) that will keep trace of the
            //       logged user
            //      
            //       Keeping states on server is worse because it will become
            //       a structure like the current PHP application which are not
            //       serverless considering the REST approach. And there will
            //       to both watch login/logout events on server and both on 
            //       client. Those cases should be studied in details, analyzing
            //       it pros & cons and pick the slution to use everywhere

            // TODO: prevent memory leaks (even on server)
            // TODO: refactor definition to be the same as Login
            if(!pending && loggedIn){
                pending = true;

                AuthActionDefinition::AuthAction auth_logout;

                auth_logout.type = "logout";
                // TODO: change to _id (this is not safe & clear)
                auth_logout.user = "";

                json json_auth = auth_logout;

                RequestDefinition::Request auth_request = RequestDefinition::createEmpty();
                        auth_request.content = json_auth.dump();

                authSocket->setBuffer(auth_request);
            }

        }


    }
}