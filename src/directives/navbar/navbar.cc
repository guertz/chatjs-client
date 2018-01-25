#include <iostream>
#include <json.hpp>

#include "navbar.h"
#include "profile/profile.h"

#include "common/web-ui/web-ui.h"
#include "common/helpers/helpers.h"
#include "common/logger/logger.h"

#include "states/auth-state/auth-state.h"

using json = nlohmann::json;
using namespace std;
using namespace WebUI;
using namespace Helpers;
using namespace States;

extern char _binary_src_directives_navbar_navbar_js_start[];

namespace Navbar {

    void Bootstrap() {

        WebUI::Execute(
            safeptr::parse_asset(
                _binary_src_directives_navbar_navbar_js_start)
        );

        AuthState::Register("Navbar", State::Auth);

        Profile::RegisterLink();
    }

    void Destroy() {
        Profile::EraseLink();
    }

    namespace State {

        void Auth(){
                
            const AuthState::AUTHSIGNAL auth_action = AuthState::getAuthAction();
                  AuthState::User       auth_user   = AuthState::getAuthUser();

            switch(auth_action){
                case AuthState::AUTHSIGNAL::LOGIN:

                    if(auth_user.is_valid())
                        Profile::Events::SetText(auth_user.name);

                    break;
                case AuthState::AUTHSIGNAL::LOGOUT:

                    Profile::Events::SetText(safestr::duplicate("Profilo"));

                    break;

                case AuthState::AUTHSIGNAL::ALL:
                default:
                
                    log_base("AuthModal", "Bad format Request");
                    break;
            }

        }
    }

}