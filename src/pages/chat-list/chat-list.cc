#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <iterator>
#include <json.hpp>

#include "chat-list.h"
#include "pages/chat-details/chat-details.h"
#include "directives/modals/chat-modal/chat-modal.h"

#include "common/web-ui/web-ui.h"
#include "common/helpers/helpers.h"

#include "states/auth-state/auth-state.h"
#include "providers/chats/chats.h"


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

        void NewChat(const char* argc) {
            Modal::ChatModal::Events::Show();
            safeptr::free_block(argc);
        }

        void UserSelected(const char* arg){
            ChatDetails::Events::OpenChat(safestr::duplicate(arg));
            safeptr::free_block(arg);
        }
    }

    namespace Auth {
        void State(const char* arg) {

            json jDat = json::parse(arg);
            
            switch(jDat["action"].get<AuthState::AUTHSIGNAL>()){
                case AuthState::AUTHSIGNAL::LOGIN:
                    if(jDat["online"].get<bool>()){
                        
                        const char* BUNDLE = js::compact(80, 3, "makeAToast('Bentornato ", jDat["name"].get<string>().c_str(), "')");

                        webview_dispatch(   WebUI::GetContext(), 
                                            WebUI::Dispatch, 
                                            safeptr::serialize(safestr::duplicate(BUNDLE))
                                        );

                        safeptr::free_block(BUNDLE);
                    }
                    break;
                case AuthState::AUTHSIGNAL::LOGOUT:
                
                    break;
            }

            safeptr::free_block(arg);
        }
    }

    namespace Chats {
        void State(const char* args){

            json newChat = json::parse(args);
            const typo_chats chat_list = ChatState::Chats::Get();
            
            ostringstream oss;
            oss<<"[";
            
            if(!chat_list.empty()){
                
                typo_chats::const_iterator it = chat_list.begin();

                while(it != chat_list.end()){

                    chat_details chat = it->second;

                    json jChat;
                        jChat["reference"] = safestr::duplicate(chat.reference);
                        jChat["from"] = newChat["jsonArgs"]["from"];

                    it++;

                    oss<<jChat.dump();

                    if(it != chat_list.end())
                        oss<<",";
                    
                }
            }

            oss<<"]";

            cout<<oss.str()<<endl;

            webview_dispatch(
                WebUI::GetContext(),
                WebUI::Dispatch,
                safeptr::serialize(safestr::duplicate(("components.ChatList.updateText('"+oss.str()+"')").c_str()))
            );
            
        }

    }

    namespace Chat {
        void State(const char* args){
            
        }
    }
}