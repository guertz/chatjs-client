#include <iostream>
#include <json.hpp>

#include "chat-modal.h"
#include "chat-modal.hjs"

#include "directives/modals/modals.h"
#include "directives/toast/toast.h"

#include "common/helpers/helpers.h"
#include "common/logger/logger.h"
#include "common/web-ui/web-ui.h"

#include "states/users-state/users-state.h"
#include "states/chat-state/chat-state.h"

using json = nlohmann::json;
using namespace std;
using namespace WebUI;
using namespace Helpers;
using namespace States;

namespace Modal { 

    namespace ChatModal {

        /** Nome identificativo del modale chat */
        static const string modalRef = "chat-modal";

        

        void RegisterModal(){

            WebUI::Execute(_src_directives_modal_chat_modal_chat_modal_js);


            WebUI::Register("Modal::ChatModal::Close", Events::Close);
            WebUI::Register("Modal::ChatModal::NewChatOpen", Events::NewChatOpen);
            
            UsersState::Register("Modal::ChatModal", State::Users);

        }

        void EraseModal () {
            
        }

        namespace Events { 
            void NewChatOpen(const string& args){

                json function = json::parse(args);

                ChatState::ChatsMethods::StartAChat(function.at("user").get<string>());
            }

            void Show() {
                State::Users();
                Modal::Events::ShowModalByRef(modalRef);  
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
            
            void Users() {
                const string serializedList = UsersState::getSerializedList();

                const string js_action = "modals.ChatModal.populateChat('" +
                            serializedList +
                        "')";

                log_base("ChatModal@Execute", js_action);
                WebUI::Execute(js_action); 
            }
        
        }
    }
}