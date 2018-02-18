#include <iostream>
#include <json.hpp>

#include "chat-list.h"
#include "chat-list.js.h"

#include "components/modals/chat-modal/chat-modal.h"
#include "components/toast/toast.h"

#include "common/web-ui/web-ui.h"
#include "common/logger/logger.h"

#include "states/auth-state/auth-state.h"
#include "states/chats-state/chats-state.h"


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
            log_details(TAG::CMP, "ChatList::NewChat", args);
            Modals::ChatModal::Events::Show();
        }

        inline void UserSelected(const std::string& args){
            log_details(TAG::CMP, "ChatList::UserSelected", args);

            json event_args = json::parse(args);
            ChatsState::setCurrentChat(event_args.at("ref").get<string>());
        }
    }

    void Bootstrap(){
        log_base(TAG::CMP, "ChatList::Bootstrap", "");

        WebUI::Execute(_src_components_chat_list_chat_list_js);

        WebUI::Register("ChatList::NewChat", Events::NewChat);
        WebUI::Register("ChatList::UserSelected", Events::UserSelected);

        ChatsState::Register("ChatList", State::Chats);

        AuthState::Register("ChatList", State::Auth);
    }

    void Destroy() {
        log_base(TAG::CMP, "ChatList::Destroy", "");
    }

    namespace State {
        
        inline void Auth() {    
            const AuthSocket::SIGNAL
                            auth_action = AuthState::getAuthAction();
            const User      auth_user   = AuthState::getAuthUser();

            switch(auth_action){
                case AuthSocket::SIGNAL::LOGIN:
                    if(auth_user.is_valid())
                        
                        Toast::Events::Show(auth_user.name);
                    
                    break;
                    
                default: 

                    break;

            }
        }

        inline void Chats() {
            const string js_context = "components.ChatList.populateChatList('" +
                                        ChatsState::getSerializedChats() +
                                      "')";
                                      
            WebUI::Execute(js_context);

            Toast::Events::Show("E stata iniziata una nuova chat.");
        }

        inline void Chat(){
            Toast::Events::Show("E stato ricevuto un messaggio.");
        }

    }

}