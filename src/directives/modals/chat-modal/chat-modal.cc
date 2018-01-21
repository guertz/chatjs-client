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

namespace Modal { 

    namespace ChatModal {

        // Deve essere lo stesso valore presente nel file JS
        static const char* modalRef = "chat-modal"; /** Nome identificativo del modale chat */

        static Socket usersStream ("users-stream", State::RefreshUsers);

        void RegisterModal(){
            
            WebUI::Register("Modal::ChatModal::NewChatOpen", Events::NewChatOpen);
            
            ChatState::Chats::Register("Modal::ChatModal", State::Chats);

            try {
                usersStream.compute();
            } catch(...) {
                log_base("AuthState", "socket error");
            }

        }

        void EraseModal () {
            usersStream.stop();
        }

        namespace Events { 
            void NewChatOpen(const char* args){

                json function = json::parse(args);
                
                json jReq;
                    jReq.at("destination") = function.at("user").at("_id");

                ChatState::Chats::StartAChat(safestr::duplicate(jReq.dump().c_str()));
            }

            void Show() {

                const char* userInSession = AuthState::getAuthStatus();

                if(userInSession){

                    // TODO: check logging status
                    json jUser = json::parse(userInSession);

                    json jReq;
                         jReq["type"] = "listen";
                         jReq["user"]["_id"] = jUser["_id"];
                
                    // TODO: structuryze
                    usersStream.setBuffer(jReq.dump(), true);

                    Modal::Events::ShowModalByRef(safestr::duplicate(modalRef));
                }

                safeptr::free_block(userInSession);
            }

            void Hide() {
                Modal::Events::HideModalByRef(safestr::duplicate(modalRef));    
            }

            
        }

        namespace State {

            void RefreshUsers(const char* args){

                const char* js_action = js::compact(strlen(args) + 50, 3, 
                                        "window.modals.ChatModal.methods.populate('", 
                                            args, 
                                        "')");

                webview_dispatch(   
                    WebUI::GetContext(), 
                    WebUI::Dispatch, 
                    safeptr::serialize(safestr::duplicate(js_action))
                );   

                safeptr::free_block(js_action); 
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