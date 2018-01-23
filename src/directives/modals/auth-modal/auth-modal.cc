#include <iostream>
#include <json.hpp>

#include "auth-modal.h"

#include "common/web-ui/web-ui.h"
#include "common/helpers/helpers.h"
#include "common/logger/logger.h"
#include "directives/modals/modals.h"

#include "states/auth-state/auth-state.h"

using json = nlohmann::json;
using namespace std;
using namespace WebUI;
using namespace Helpers;
using namespace States;

extern char _binary_src_directives_modals_auth_modal_auth_modal_js_start[];

namespace Modal {

    namespace AuthModal {

        // Deve essere lo stesso valore presente nel file JS
        static const char* modalRef = "auth-modal"; /** Nome identificativo del modale di autenticazione */
        
        namespace Events {

            void Submit(const char* args){

                log_base("Modal::AuthModal::Events", args);

                AuthState::AuthActionDefinition::AuthAction data = json::parse(args);

                AuthState::Login(data);

                safeptr::free_block(args);
            }

            void Reset(){
                
                const char* AUTH_RESET = js::compact(50, 1, "modals.AuthModal.reset()");

                WebUI::Execute(AUTH_RESET);

                safeptr::free_block(AUTH_RESET);
            }

            void Show() {
                Modal::Events::ShowModalByRef(safestr::duplicate(modalRef));
            }

            void Hide() {
                Modal::Events::HideModalByRef(safestr::duplicate(modalRef));
            }

        }

        void RegisterModal(){

            WebUI::Execute(
                    safeptr::parse_asset(
                        _binary_src_directives_modals_auth_modal_auth_modal_js_start)
                );
            
            WebUI::Register("Modal::AuthModal::Submit", Events::Submit);
            AuthState::Register("Modal::AuthModal", State::Auth);

           Events::Show();
            
        }

        void EraseModal () {
            
        }

        namespace State {
                
            void Auth(const char* arg){

                Events::Reset();

                json json_auth = json::parse(arg);

                switch(json_auth["action"].get<AuthState::AUTHSIGNAL>()){
                    case AuthState::AUTHSIGNAL::LOGIN:
                        if(json_auth["online"].get<bool>()){
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

                const char* AUTH_ERRORS = js::compact(50, 1, "modals.AuthModal.showErrors()");

                WebUI::Execute(AUTH_ERRORS);
                // Events::Reset

                safeptr::free_block(AUTH_ERRORS);

            }

            void OnLogout () {
                Events::Show();
            }
        }

    }
}