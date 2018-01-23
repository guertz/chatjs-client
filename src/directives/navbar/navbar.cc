#include<iostream>
#include<json.hpp>

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

        void Auth(const char* arg){

            json json_auth = json::parse(arg);

            switch(json_auth.at("action").get<AuthState::AUTHSIGNAL>()){
                case AuthState::AUTHSIGNAL::LOGIN:

                    if(json_auth.at("online").get<bool>())
                        Profile::Events::SetText(safestr::duplicate(json_auth.at("user").at("name").get<string>().c_str()));

                    break;
                case AuthState::AUTHSIGNAL::LOGOUT:

                    Profile::Events::SetText(safestr::duplicate("Profilo"));

                    break;
            }

            safeptr::free_block(arg);
        }
    }

}