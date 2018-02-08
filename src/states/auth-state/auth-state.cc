#include <iostream>
#include <map>
#include <json.hpp>

#include "auth-state.h"
#include "protocol/sockets/wscustom.h"

#include "common/logger/logger.h"

using json = nlohmann::json;
using namespace ws;
using namespace std;

namespace States {
    
    namespace AuthState {

        static Socket* authSocket = 0;
        static bool pending       = false;
        
        static AuthResponse authResponse;

        static Subscribers subscribed;

        void notify(){
            
            for (const auto& item : subscribed)
                (*item.second)(); 

        }

        void ResponseSuccess(const std::string str_response) {

            log_base("Auth", str_response);

            authResponse = AuthResponse(str_response);
            pending = false;

            notify();
        }

        void ResponseError(const std::string str_error) {
            
            log_base("Auth", str_error);

            AuthResponse response_errors;
                         response_errors.type  = AUTHSIGNAL::LOGIN; 
                         response_errors.error = str_error;

            authResponse = response_errors;
            pending = false;

            notify();
        }

        AUTHSIGNAL getAuthAction() {
            return authResponse.type;
        }

        User getAuthUser() {
            return authResponse.user;
        }

        std::string getAuthError() {
            return authResponse.error;
        }

        void Bootstrap() {
            
            if(!authSocket)
                authSocket = new Socket("auth", ResponseSuccess, ResponseError);

        }

        void Destroy() {
            if(authSocket){
                delete authSocket;
                       authSocket = 0;
            }
        }


        void Register(std::string cb_name, void (*fn)()){
            subscribed[cb_name] = fn;
        }

        void Login(const std::string& AUTH_KEY){

            // assert
            if(!pending && !authResponse.online){
                pending = true;
                
                AuthRequest auth_request;
                    auth_request.type = AUTHSIGNAL::LOGIN;
                    auth_request.user = AUTH_KEY;


                BaseRequest socket_data;
                            socket_data.content = auth_request.serialize();

                authSocket->setBuffer(socket_data);
            }

        }

        void Logout(){
            // Observable to prevent inconsistent auth state

            if(!pending && authResponse.online){
                pending = true;


                Request::Auth auth_request;
                    auth_request.type = AUTHSIGNAL::LOGOUT;
                    // auth_request.user = "";

                
                BaseRequest socket_data;
                            socket_data.content = auth_request.serialize();
                            socket_data.AUTH    = authResponse.user._id;

                authSocket->setBuffer(socket_data);

            }

        }


    }
}