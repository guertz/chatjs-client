#include <iostream>
#include <json.hpp>

#include "chat-modal.h"
#include "chat-modal.hjs"

#include "directives/modals/modals.h"

#include "common/logger/logger.h"
#include "common/web-ui/web-ui.h"

#include "states/users-state/users-state.h"
#include "states/chat-state/chat-state.h"

using json = nlohmann::json;
using namespace std;
using namespace WebUI;
using namespace States;

namespace Modals { 

    namespace ChatModal {

        /** Nome identificativo del modale chat */
        static const string modalRef = "chat-modal";

        static const string CHAT_DESTROY = "modals.AuthModal.destroy()";

        namespace Events { 
            inline void NewChatOpen(const string& args){
                log_pedantic("ChatModal::Submit", args);

                json function = json::parse(args);
                ChatState::ChatsMethods::StartAChat(function.at("user").get<string>());
            }

            void Show() {
                State::Users(); // Refresh forzato
                Modals::Events::ShowModalByRef(modalRef);  
            }

            void Hide() {
                Modals::Events::HideModalByRef(modalRef);    
            }            
        }

        void RegisterModal(){
            log_details("ChatModal", "Create");

            WebUI::Execute(_src_directives_modal_chat_modal_chat_modal_js);

            WebUI::Register("Modals::ChatModal::NewChatOpen", Events::NewChatOpen);
            UsersState::Register("Modals::ChatModal", State::Users);
        }

        void EraseModal () {
            log_details("ChatModal", "Erase");

            WebUI::Execute(CHAT_DESTROY);
        }

        namespace State {
            
            inline void Users() {
                log_details("ChatModal::State::Users", "Refreshing...");

                const string serializedList = UsersState::getSerializedList();

                const string js_action = "modals.ChatModal.populateChat('" +
                            serializedList +
                        "')";

                WebUI::Execute(js_action); 
            }
        
        }
    }
}