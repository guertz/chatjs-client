#include <iostream>
#include <json.hpp>

#include "chat-modal.h"
#include "directives/modals/modals.h"
#include "directives/toast/toast.h"

#include "common/helpers/helpers.h"
#include "common/logger/logger.h"
#include "common/web-ui/web-ui.h"

#include "states/auth-state/auth-state.h"
#include "states/chat-state/chat-state.h"

#include "protocol/sockets/wscustom.h"

using json = nlohmann::json;
using namespace std;
using namespace WebUI;
using namespace Helpers;
using namespace States;
using namespace ws;

namespace Modal { 

    namespace ChatModal {

        /** Nome identificativo del modale chat */
        static const string modalRef = "chat-modal";

        static Socket *usersStream = 0;

        void RegisterModal(){

            try {
                 usersStream = new Socket(  "users-stream", 
                                            State::RefreshUsersSuccess, 
                                            State::RefreshUsersError);
            } catch(...) {
                log_base("ChatModal::Socket>>'users-stream'", "Exception reported");
            }

            WebUI::Register("Modal::ChatModal::Close", Events::Close);
            WebUI::Register("Modal::ChatModal::NewChatOpen", Events::NewChatOpen);
            
            ChatState::Chats::Register("Modal::ChatModal", State::Chats);

        }

        void EraseModal () {
            // Use method
            if(usersStream){
                delete usersStream;
                       usersStream = 0;
            }
        }

        namespace Events { 
            void NewChatOpen(const string& args){

                json function = json::parse(args);
                
                json jReq;
                    jReq.at("destination") = function.at("user").at("_id");

                ChatState::Chats::StartAChat(jReq.dump());
            }

            void Show() {

                const AuthState::UserDefinition::User auth_user = AuthState::getAuthUser();

                if(auth_user._id.size()>0){

                    json populate_request = {{"type", "listen"}, {"user", auth_user._id}};

                    RequestDefinition::Request request = RequestDefinition::createEmpty();
                            
                        request.content =  populate_request.dump();
                        
                    usersStream->setBuffer(request);

                    Modal::Events::ShowModalByRef(modalRef);
                }
            }

            // Todo: JS Close bind Event
            void Close(const string& args) {
                Hide();
            }

            void Hide() {
                Modal::Events::HideModalByRef(modalRef);    
            }

            
        }

        namespace State {

            void RefreshUsersSuccess(const string success){

                const string js_action = "window.modals.ChatModal.methods.populate('" +
                                            success +
                                        "')";

                WebUI::Execute(js_action); 
            }

            // TODO: remove all c_str make string
            void RefreshUsersError(const string errors){
                log_base("ChatModal::Socket>>'users-stream'", "Received error: " +errors);
            }
            
            void Chats(const string& args){

                json newChat = json::parse(args);
                
                if(strcmp(newChat["destination"].dump().c_str(), newChat["creator"].dump().c_str()) == 0){
                    
                    Events::Hide();
                    
                    // posso scrivere dopo socket stop?
                    // MakeAToast ? 
                }
            }
        }
    }
}