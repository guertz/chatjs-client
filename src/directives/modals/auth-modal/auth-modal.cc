#include <iostream>
#include <json.hpp>

#include "auth-modal.h"
#include "auth-modal.hjs"

#include "directives/modals/modals.h"

#include "common/web-ui/web-ui.h"
#include "common/logger/logger.h"

#include "states/auth-state/auth-state.h"

using json = nlohmann::json;
using namespace std;
using namespace WebUI;
using namespace States;

namespace Modals {

    namespace AuthModal {

        /** Nome identificativo del modale di autenticazione */
        static const string modalRef = "auth-modal";  // Deve essere lo stesso valore presente nel file JS

        static const string AUTH_RESET = "modals.AuthModal.reset()";
        static const string AUTH_DESTROY = "modals.AuthModal.destroy()";
        static const string AUTH_ERRORS = "modals.AuthModal.showErrors()";

        namespace Events {

            inline void Submit(const string& args){
                log_pedantic("AuthModal::Submit", args);

                json fn_params = json::parse(args);
                AuthState::Login(fn_params.at("_id").get<string>());
            }

            void Reset(){
                log_pedantic("AuthModal::Reset", "");

                WebUI::Execute(AUTH_RESET);
            }

            void Show() {
                Modals::Events::ShowModalByRef(modalRef);
            }

            void Hide() {
                Modals::Events::HideModalByRef(modalRef);
            }

        }

        void RegisterModal(){
            log_details("AuthModal", "Create");

            WebUI::Execute(_src_directives_modal_auth_modal_auth_modal_js);
            
            WebUI::Register("Modals::AuthModal::Submit", Events::Submit);
            AuthState::Register("Modals::AuthModal", State::Auth);

            Events::Show();
        }

        void EraseModal () {
            log_details("AuthModal", "Erase");

            WebUI::Execute(AUTH_DESTROY);
        }

        namespace State {
                
            inline void Auth(){
                log_pedantic("AuthModal::State::Auth", "Refreshing...");
                
                Events::Reset();

                const AuthState::AUTHSIGNAL 
                            auth_action = AuthState::getAuthAction();
                const User  auth_user   = AuthState::getAuthUser();

                switch(auth_action) {
                    case AuthState::AUTHSIGNAL::LOGIN:
                        if(auth_user.is_valid())
                            AuthMethods::OnLoginSuccess();
                        else
                            AuthMethods::OnLoginErrors();
                        
                        break;

                    case AuthState::AUTHSIGNAL::LOGOUT:
                        AuthMethods::OnLogout();

                        break;
                }
            }
        }

        namespace AuthMethods {

            inline void OnLoginSuccess() {
                Events::Hide();
            }

            inline void OnLoginErrors() {
                WebUI::Execute(AUTH_ERRORS);
            }

            inline void OnLogout () {
                Events::Show();
            }
        }

    }
}