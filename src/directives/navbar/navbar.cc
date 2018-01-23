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

        void Auth(const AuthState::AuthBaseDefinition::AuthBase& auth_data){

            switch(auth_data.action){
                case AuthState::AUTHSIGNAL::LOGIN:

                    if(auth_data.online)
                        Profile::Events::SetText(auth_data.user.name);

                    break;
                case AuthState::AUTHSIGNAL::LOGOUT:

                    Profile::Events::SetText(safestr::duplicate("Profilo"));

                    break;
            }

        }
    }

}