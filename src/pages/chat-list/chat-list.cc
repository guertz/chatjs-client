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

#include "states/chat-state/chat-state.h"


using json = nlohmann::json;
using namespace std;
using namespace ws;
using namespace WebUI;
using namespace Helpers;
using namespace States;

// ToastifyNewChat(safestr::duplicate(Chatters["jsonArgs"]["from"].dump().c_str()));
// void ToastifyNewChat(const char* args){
//     json jDat = json::parse(args);

//     const char* BUNDLE = js::compact(80, 3, "makeAToast('E stata iniziata una chat con ", jDat["name"].get<string>().c_str(), "')");

//     webview_dispatch(   WebUI::GetContext(), 
//                         WebUI::Dispatch, 
//                         safeptr::serialize(safestr::duplicate(BUNDLE))
//                     );

//     safeptr::free_block(BUNDLE);
//     safeptr::free_block(args);
// }

namespace ChatList {
    void Bootstrap(){
        WebUI::Register("ChatList::NewChat", Events::NewChat);
        WebUI::Register("ChatList::UserSelected", Events::UserSelected);

        ChatState::Chats::Register("ChatList", Chats::State);
        AuthState::Register("ChatList", Auth::State);
    }

    namespace Events { 

        void NewChat(const string& argc) {
            Modal::ChatModal::Events::Show();
        }

        void UserSelected(const string& arg){
            ChatDetails::Events::OpenChat(arg);
        }
    }

    namespace Auth {
        void State(const AuthState::AuthBaseDefinition::AuthBase& auth_data) {

            switch(auth_data.action){
                case AuthState::AUTHSIGNAL::LOGIN:
                    if(auth_data.online)
                        
                        Toast::Events::Show(auth_data.user.name);
                    
                    break;
                case AuthState::AUTHSIGNAL::LOGOUT:
                
                    break;
            }
        }
    }

    namespace Chats {
        void State(const string& args){

            json newChat = json::parse(args);
            const ChatState::typo_chats chat_list = ChatState::Chats::Get();
            
            ostringstream oss;
            oss<<"[";
            
            if(!chat_list.empty()){
                
                ChatState::typo_chats::const_iterator it = chat_list.begin();

                while(it != chat_list.end()){

                    ChatState::chat_details chat = it->second;

                    json jChat;
                        jChat["reference"] = chat.reference;
                        jChat["from"] = newChat["jsonArgs"]["from"];

                    it++;

                    oss<<jChat.dump();

                    if(it != chat_list.end())
                        oss<<",";
                    
                }
            }

            oss<<"]";

            cout<<oss.str()<<endl;

            const string js_context = "components.ChatList.updateText('" + oss.str() + "')";
            
            WebUI::Execute(js_context);
            
        }

    }

    namespace Chat {
        void State(const string& args){
            
        }
    }
}