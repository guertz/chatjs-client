#include <iostream>
#include <map>
#include <json.hpp>

#include "users-state.h"
#include "states/auth-state/auth-state.h"

#include "protocol/sockets/wscustom.h"

#include "common/helpers/helpers.h"
#include "common/logger/logger.h"

using json = nlohmann::json;
using namespace ws;
using namespace std;
using namespace Helpers;

namespace States {
    namespace UsersState {

        static Socket *usersSocket = 0;
        static Response::Stream streamResponse;

        static Subscribers subscribed;

        void notify(const Response::Stream& stream){
            
            streamResponse = stream;

            for (const auto& item : subscribed)
                (*item.second)();
            
        }
        
        void Register(string abc, void (*fn)()){
            subscribed[abc] = fn;
        }

        void Bootstrap() {
            
            AuthState::Register("UsersState", State::Auth);

            try {
                if(!usersSocket)
                    usersSocket = new Socket(   "users-stream", 
                                                Sockets::UsersStream::ResponseSuccess, 
                                                Sockets::UsersStream::ResponseError);
            }catch(...) {
                log_base("UsersState::Socket>>'users-stream'", "Exception reported");
            }

        }

        void Destroy() {
            if(usersSocket){
                delete usersSocket;
                       usersSocket = 0;
            }
        }

        const string& getSerializedList() {
            return streamResponse.usersList;    
        }

        namespace Sockets {
            namespace UsersStream {

                static bool streaming = false;

                inline void Init(const string& AUTH) {
                    
                    if(!streaming){
                        streaming = true;
                
                        Request::Stream stream_request;
                            stream_request.type = STREAMSIGNAL::OPEN;

                        
                        BaseRequest socket_data;
                            socket_data.content = stream_request.serialize();
                            socket_data.AUTH = AUTH;

                        usersSocket->setBuffer(socket_data);
                        
                    }
                }

                inline void Close() {

                    if(streaming) {
                        Request::Stream stream_request;
                            stream_request.type = STREAMSIGNAL::CLOSE;

                    
                        BaseRequest socket_data;
                            socket_data.content = stream_request.serialize();

                        // streaming = false && after that compute = stop?
                        usersSocket->setBuffer(socket_data);

                        streaming = false;
                    }

                }

                inline void ResponseSuccess(const string str_response) {

                    // check reponse type and do action
                    // update static variables data

                    Response::Stream stream_response(json::parse(str_response));

                    notify(stream_response);
                }

                inline void ResponseError(const string str_error) {
                    
                    // TODO: failure this variable will die
                    //       but notify is copying first
                    // Cannot cast because of content undefined
                    Response::Stream stream_response;

                    notify(stream_response);
                }
            }
        }

        namespace State {
            void Auth() {

                const AuthState::AUTHSIGNAL auth_action = AuthState::getAuthAction();
                      AuthState::User       auth_user   = AuthState::getAuthUser();

                switch(auth_action) {

                    case AuthState::AUTHSIGNAL::LOGIN:

                        if(auth_user.is_valid())
                            Sockets::UsersStream::Init(auth_user._id);
                        // else
                        //   no channel should be opened (useless)

                        break;

                    case AuthState::AUTHSIGNAL::LOGOUT:

                        Sockets::UsersStream::Close();

                        break;
                    
                    case AuthState::AUTHSIGNAL::ALL:
                    default:
                    
                        // if network crashed i would like to stop the stream
                        // but the cannel is fuckedup
                        log_base("AuthModal", "Bad format Request");
                        break;
                }
                
            }
        }
    }
}