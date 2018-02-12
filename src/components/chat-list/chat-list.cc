#include <iostream>
#include <json.hpp>

#include "chat-list.h"
#include "chat-list.hjs"

#include "components/modals/chat-modal/chat-modal.h"
#include "components/toast/toast.h"

#include "common/web-ui/web-ui.h"
#include "common/logger/logger.h"

#include "states/auth-state/auth-state.h"
#include "states/chat-state/chat-state.h"


using json = nlohmann::json;
using namespace std;
using namespace States;

/**
 * @brief Definizione pagina ChatList in cui vengono visualizzate la chat aperte
 * @file chat-list.cc
 */

namespace ChatList {

    namespace Events { 

        inline void NewChat(const std::string& args) {
            log_C(TAG::CMP, "ChatList::NewChat", args);
            Modals::ChatModal::Events::Show();
        }

        inline void UserSelected(const std::string& args){
            log_C(TAG::CMP, "ChatList::UserSelected", args);

            json event_args = json::parse(args);
            ChatState::ChatsMethods::setCurrent(event_args.at("ref").get<string>());
        }
    }

    void Bootstrap(){
        log_B(TAG::CMP, "ChatList::Bootstrap", "");

        WebUI::Execute(_src_components_chat_list_chat_list_js);

        WebUI::Register("ChatList::NewChat", Events::NewChat);
        WebUI::Register("ChatList::UserSelected", Events::UserSelected);

        ChatState::ChatsMethods::Register("ChatList", State::Chats);

        AuthState::Register("ChatList", State::Auth);
    }

    void Destroy() {
        log_B(TAG::CMP, "ChatList::Destroy", "");
    }

    namespace State {
        
        inline void Auth() {    
            const AuthState::SIGNAL
                            auth_action = AuthState::getAuthAction();
            const User      auth_user   = AuthState::getAuthUser();

            switch(auth_action){
                case SIGNAL::LOGIN:
                    if(auth_user.is_valid())
                        
                        Toast::Events::Show(auth_user.name);
                    
                    break;
                    
                default: 

                    break;

            }
        }

        inline void Chats() {
            const string js_context = "components.ChatList.populateChatList('" +
                                        ChatState::ChatsMethods::getSerializedChats() +
                                      "')";
                                      
            WebUI::Execute(js_context);

            Toast::Events::Show("E stata iniziata una nuova chat.");
        }

        inline void Chat(){
            Toast::Events::Show("E stato ricevuto un messaggio.");
        }

    }

}