#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <iterator>
#include <json.hpp>

#include "chat-list.h"
#include "pages/chat-details/chat-details.h"

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

        // ChatState::Chats::Register("ChatList", Chats::State);
        // ChatState::Chat::Register("ChatList", Chat::State);

        AuthState::Register("ChatList", Auth::State);
    }

    namespace Events { 

        void NewChat(const string& argc) {
            // log_base("ChatList::Events(NewChat)", argc);
            Modal::ChatModal::Events::Show();
        }

        void UserSelected(const string& arg){
            ChatDetails::Events::OpenChat(arg);
        }
    }

    namespace Auth {
        void State() {
            
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
    }

    // namespace Chats {
    //     void State(const string& args){

    //         json newChat = json::parse(args);
    //         const ChatState::typo_chats chat_list = ChatState::Chats::Get();
            
    //         ostringstream oss;
    //         oss<<"[";
            
    //         if(!chat_list.empty()){
                
    //             ChatState::typo_chats::const_iterator it = chat_list.begin();

    //             while(it != chat_list.end()){

    //                 ChatState::chat_details chat = it->second;

    //                 json jChat;
    //                     jChat["reference"] = chat.reference;
    //                     jChat["from"] = newChat["jsonArgs"]["from"];

    //                 it++;

    //                 oss<<jChat.dump();

    //                 if(it != chat_list.end())
    //                     oss<<",";
                    
    //             }
    //         }

    //         oss<<"]";

    //         cout<<oss.str()<<endl;

    //         const string js_context = "components.ChatList.populateChatList('" + oss.str() + "')";
            
    //         WebUI::Execute(js_context);

    //         Toast::Events::Show("E' stata iniziata una nuova chat con ...");
            
    //     }

    // }

    // namespace Chat {
    //     void State(){
    //         Toast::Events::Show("E' stato ricevuto un nuovo messaggio da ....");
    //     }   
    // }
}