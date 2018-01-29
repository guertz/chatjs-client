#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <iterator>
#include <json.hpp>

#include "chat-list.h"

#include "directives/modals/chat-modal/chat-modal.h"
#include "directives/toast/toast.h"

#include "common/web-ui/web-ui.h"
#include "common/helpers/helpers.h"
#include "common/logger/logger.h"

#include "states/chat-state/chat-state.h"


using json = nlohmann::json;
using namespace std;
using namespace ws;
using namespace WebUI;
using namespace Helpers;
using namespace States;

extern char _binary_src_pages_chat_list_chat_list_js_start[];

namespace ChatList {
    void Bootstrap(){

        WebUI::Execute(
                safeptr::parse_asset(
                    _binary_src_pages_chat_list_chat_list_js_start)
            );

        WebUI::Register("ChatList::NewChat", Events::NewChat);
        WebUI::Register("ChatList::UserSelected", Events::UserSelected);

        ChatState::ChatsMethods::Register("ChatList", State::Chats);

        AuthState::Register("ChatList", State::Auth);
    }

    namespace Events { 

        void NewChat(const string& argc) {
            // log_base("ChatList::Events(NewChat)", argc);
            Modal::ChatModal::Events::Show();
        }

        void UserSelected(const string& arg){

            // log_base("ChatList@UserSelected", arg);

            json event_args = json::parse(arg);
            ChatState::ChatsMethods::setCurrent(event_args.at("ref").get<string>());
        }
    }

    namespace State {
        void Auth() {
            
            const AuthState::AUTHSIGNAL auth_action = AuthState::getAuthAction();
                             User       auth_user   = AuthState::getAuthUser();

            switch(auth_action){
                case AuthState::AUTHSIGNAL::LOGIN:
                    if(auth_user.is_valid())
                        
                        Toast::Events::Show(auth_user.name);
                    
                    break;
                case AuthState::AUTHSIGNAL::LOGOUT:
                
                    break;
                case AuthState::AUTHSIGNAL::ALL:
                default:
                    log_base("AuthModal", "Bad format Request");
                    break;
            }
        }

        void Chats() {


            const string js_context = "components.ChatList.populateChatList('" +
                                        ChatState::ChatsMethods::getSerializedChats() +
                                      "')";
            log_base("ChatList>>Refetch", js_context);
            WebUI::Execute(js_context);

            Toast::Events::Show("E stata iniziata una nuova chat.");
            
        }

        void Chat(){
            Toast::Events::Show("E stato ricevuto un messaggio.");
        }

    }

}