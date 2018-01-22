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
    namespace AuthState {

        void receiveLoginAction(const char* args);

        static Socket* authSocket;
        static bool pending       = false;
        static bool loggedIn      = false;
        static char* cached       = 0;

        static Subscribers subscribed;

        // Static || Inline
        void notify(const char* args){
            
            safeptr::free_block(cached);
            cached = safestr::duplicate(args);

            for (const auto& item : subscribed) {
                
                (*item.second)(safestr::duplicate(args));
            }

            safeptr::free_block(args);

        }

        const char* getAuthStatus(){
            return cached ? safestr::duplicate(cached) : 0;
        }

        void Bootstrap() {
            authSocket = new Socket("users", receiveLoginAction);

            try {
                authSocket->compute();
            }catch(...) {
                log_base("AuthState", "socket error");
            }

        }

        void Destroy() {
            authSocket->stop();
            // delete
        }


        void Register(string abc, void (*fn)(const char* arg)){
            subscribed[abc] = fn;
        }

        // Static || Inline
        // throw exception on auth failure
        // empty args
        void receiveLoginAction(const char* args){

            log_base("AuthState::LoginResponse", args);

            json auth_response = json::parse(args);

            AuthBaseDefinition::AuthBase auth_data {
                AUTHSIGNAL::LOGIN,
                false
            };

            auth_data.online = auth_response.at("online");                    

            json report = auth_data;
                    
            notify(safestr::duplicate(report.dump().c_str()));

            pending = false;

        }

        void Login(AuthActionDefinition::AuthAction& auth){
            if(!pending && !loggedIn){
                pending = true;
                
                // Changes on server
                //      1) request format
                //      2) reponse format
                //      3) auth request
                json request = auth;

                log_base("Login", request.dump().c_str());
                authSocket->setBuffer(request.dump(), false);
            }

        }

        void Logout(){
            AuthBaseDefinition::AuthBase auth_base;
                auth_base.action = AUTHSIGNAL::LOGOUT;
                json report = auth_base;

            notify(safestr::duplicate(report.dump().c_str()));

        }


    }
}