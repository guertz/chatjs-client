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

        static Socket authSocket  ("users", receiveLoginAction);
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

            try {
                authSocket.compute();
            }catch(...) {
                log_base("AuthState", "socket error");
            }

        }

        void Destroy() {
            authSocket.stop();
        }


        void Register(string abc, void (*fn)(const char* arg)){
            subscribed[abc] = fn;
        }

        // Static || Inline
        // throw exception on auth failure
        // empty args
        void receiveLoginAction(const char* args){

            // try catch if json valid
            // check is a valid json response
            try {
                json jIntern = json::parse(args);
                
                jIntern["attributes"]["action"] = AuthState::AUTHSIGNAL::LOGIN;

                // if success not found, handle exception
                if(!jIntern.at("content").at("success").get<int>()){
                    
                    jIntern["attributes"]["online"] = true;
                    AuthUserDefinition::AuthUser auth_success = jIntern.at("attributes");
                    json report = auth_success;
                    
                    notify(safestr::duplicate(report.dump().c_str()));
                    

                }

            // catch (json::parse_error &e)
            } catch (...) {

                AuthBaseDefinition::AuthBase auth_base {
                        AUTHSIGNAL::LOGIN,
                        false
                    };

                json report = auth_base;
                
                notify(safestr::duplicate(report.dump().c_str()));

                log_base("JSON::AuthState::Login", "Error parsing");
            }

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
                authSocket.setBuffer(request.dump(), false);
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