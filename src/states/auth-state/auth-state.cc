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
        static bool logged        = false;
        
        static Response::Auth authResponse;

        static Subscribers subscribed;

        void notify(const Response::Auth& auth){
            
            authResponse = auth;

            for (const auto& item : subscribed)
                (*item.second)(); 

        }

        // TODO: pass json data?
        //       pass serialized data
        //       <template> with response type casting
        //       move to sockets namespace
        void ResponseSuccess(const string str_response) {

            log_base("Auth", str_response);

            Response::Auth auth_response(json::parse(str_response));
            logged = auth_response.online;
            pending = false;

            notify(auth_response);
        }

        void ResponseError(const string str_error) {
            
            log_base("Auth", str_error);

            // Cannot cast because of content undefined
            // Do i really need to handle auth::ALL
            Response::Auth auth_response;
                           auth_response.error = str_error;
                           
            logged = false;
            pending = false;

            notify(auth_response);
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


        void Register(string abc, void (*fn)()){
            subscribed[abc] = fn;
        }

        void Login(const string& AUTH_KEY){

            // assert
            if(!pending && !logged){
                pending = true;
                
                Request::Auth auth_request;
                    auth_request.type = AUTHSIGNAL::LOGIN;
                    auth_request.user = AUTH_KEY;


                BaseRequest socket_data;
                            socket_data.content = auth_request.serialize();

                authSocket->setBuffer(socket_data);
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
            if(!pending && logged){
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