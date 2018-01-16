#include <iostream>
#include <json.hpp>

#include "common/helpers/web_ui.h"
#include "common/helpers/helpers.h"

#include "auth-modal.h"

#include "common/modal/modal.h"

#include "providers/session/authstate.h"

using json = nlohmann::json;
using namespace std;
using namespace WebUI;
using namespace Helpers;


extern char _binary_src_modals_auth_modal_auth_modal_js_start[];

namespace Modal {

    namespace AuthModal {

        // Deve essere lo stesso valore presente nel file JS
        static const char* modalRef = "auth-modal"; /** Nome identificativo del modale di autenticazione */
        
        namespace Events {

            void Submit(const char* args){
                AuthState::Login(safestr::duplicate(args));

                safeptr::free_block(args);
            }

            void Reset(){
                
                // const char* js_action = js::compact(50, 1, "window.modals.AuthModal.methods.reset()");

                // webview_dispatch(   
                //     WebUI::GetContext(),
                //     WebUI::Dispatch,
                //     safeptr::serialize(safestr::duplicate(js_action))
                // );

                // safeptr::free_block(js_action);
            }

            void Show() {
                // Modal::Events::ShowModalByRef(safestr::duplicate(modalRef));
            }

            void Hide() {
                // Modal::Events::HideModalByRef(safestr::duplicate(modalRef));
            }

        }

        void RegisterModal(){

            WebUI::Execute(
                    safeptr::parse_asset(
                        _binary_src_modals_auth_modal_auth_modal_js_start)
                );
            // WebUI::Register("Modal::AuthModal::Submit", Events::Submit);
            // AuthState::Register("Modal::AuthModal", State::Auth);

           // Events::Show();
            
        }

        void EraseModal () {
            
        }

        namespace State {
                
            void Auth(const char* arg){

                Events::Reset();

                json jDat = json::parse(arg);

                switch(jDat["action"].get<AuthState::AUTHSIGNAL>()){
                    case AuthState::AUTHSIGNAL::LOGIN:
                        if(!jDat["failure"].get<bool>()){
                            AuthMethods::OnLoginSuccess();
                        } else {
                            AuthMethods::OnLoginErrors();
                        }
                            
                        break;

                    case AuthState::AUTHSIGNAL::LOGOUT:

                        AuthMethods::OnLogout();

                        break;
                }

                safeptr::free_block(arg);
                
            }
        }

        namespace AuthMethods {

            void OnLoginSuccess() {
                Events::Hide();
            }

            void OnLoginErrors() {

                // const char* JS_MODAL_AUTH_ERRORS = js::compact(50, 1, "alert('wrong attributes')");

                // webview_dispatch(   
                //     WebUI::GetContext(),
                //     WebUI::Dispatch, 
                //     safeptr::serialize(safestr::duplicate(JS_MODAL_AUTH_ERRORS))
                // );

                // safeptr::free_block(JS_MODAL_AUTH_ERRORS);

            }

            void OnLogout () {
                Events::Show();
            }
        }

    }
}