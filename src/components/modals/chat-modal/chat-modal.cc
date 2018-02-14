#include <iostream>
#include <json.hpp>

#include "chat-modal.h"
#include "chat-modal.js.h"

#include "components/modals/modals.h"

#include "common/logger/logger.h"
#include "common/web-ui/web-ui.h"

#include "states/users-state/users-state.h"
#include "states/chats-state/chats-state.h"

using json = nlohmann::json;
using namespace std;
using namespace WebUI;
using namespace States;

/**
 * @brief Definizione ChatModal, modale per iniziareuna chat
 * @file chat-modal.cc
 */

namespace Modals { 

    namespace ChatModal {

        /** Nome identificativo del modale chat */
        static const string modalRef = "chat-modal";

        static const string CHAT_DESTROY = "modals.AuthModal.destroy()";

        namespace Events { 
            inline void NewChatOpen(const std::string& args){
                log_C(TAG::CMP, "Modals::ChatModal::NewChatOpen", args);

                json function = json::parse(args);
                ChatsState::StartAChat(function.at("user").get<string>());
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
            log_B(TAG::CMP, "Modals::ChatModal::RegisterModal", "");

            WebUI::Execute(_src_components_modal_chat_modal_chat_modal_js);

            WebUI::Register("Modals::ChatModal::NewChatOpen", Events::NewChatOpen);
            UsersState::Register("Modals::ChatModal", State::Users);
        }

        void EraseModal () {
            log_B(TAG::CMP, "Modals::ChatModal::EraseModal", "");

            WebUI::Execute(CHAT_DESTROY);
        }

        namespace State {
            
            inline void Users() {
                const string serializedList = UsersState::getSerializedList();

                const string js_action = "modals.ChatModal.populateChat('" +
                            serializedList +
                        "')";

                WebUI::Execute(js_action); 
            }
        
        }
    }
}