#include <iostream>
#include <json.hpp>

#include "chat-modal.h"

#include "common/helpers/helpers.h"
#include "common/logger/logger.h"
#include "common/web-ui/web-ui.h"

#include "directives/modals/modals.h"
#include "directives/toast/toast.h"

#include "states/auth-state/auth-state.h"
#include "protocol/sockets/wscustom.h"
#include "providers/chats/chats.h"

using json = nlohmann::json;
using namespace std;
using namespace WebUI;
using namespace Helpers;
using namespace States;
using namespace ws;

namespace Modal { 

    namespace ChatModal {

        // Deve essere lo stesso valore presente nel file JS
        static const char* modalRef = "chat-modal"; /** Nome identificativo del modale chat */

        static Socket *usersStream = 0;

        void RegisterModal(){

            try {
                 usersStream = new Socket(  "users-stream", 
                                            State::RefreshUsersSuccess, 
                                            State::RefreshUsersError);
            } catch(...) {
                log_base("ChatModal::Socket>>'users-stream'", "Exception reported");
            }

            WebUI::Register("Modal::ChatModal::Hide", Events::Hide);
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
            void NewChatOpen(const char* args){

                json function = json::parse(args);
                
                json jReq;
                    jReq.at("destination") = function.at("user").at("_id");

                ChatState::Chats::StartAChat(jReq.dump().c_str());
            }

            void Show() {

                const char* userInSession = AuthState::getAuthStatus();

                if(userInSession){

                    // TODO: check logging status
                    json auth_user = json::parse(userInSession).at("content");
                    json populate_request = {{"type", "listen"}, {"user", auth_user.at("_id").get<string>()}};

                    RequestDefinition::Request request = RequestDefinition::createEmpty();
                            
                        request.content =  populate_request.dump();
                        
                    usersStream->setBuffer(request);

                    Modal::Events::ShowModalByRef(safestr::duplicate(modalRef));
                }

                safeptr::free_block(userInSession);
            }

            void Hide(const char* args) {
                Hide();
                safeptr::free_block(args);
            }

            void Hide() {
                Modal::Events::HideModalByRef(safestr::duplicate(modalRef));    
            }

            
        }

        namespace State {

            void RefreshUsersSuccess(const string success){

                const string js_action = "window.modals.ChatModal.methods.populate('" +
                                            success +
                                        "')";

                WebUI::Execute(js_action.c_str()); 
            }

            // TODO: remove all c_str make string
            void RefreshUsersError(const string errors){
                log_base("ChatModal::Socket>>'users-stream'", ("Received error: " +errors).c_str());
            }
            
            void Chats(const char* args){

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