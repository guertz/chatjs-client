#include<iostream>
#include<json.hpp>

#include "navbar.h"

#include "navbar/profile/profile.h"

#include "common/helpers/web_ui.h"
#include "common/helpers/helpers.h"

#include "providers/session/authstate.h"

using json = nlohmann::json;
using namespace std;
using namespace WebUI;
using namespace Helpers;

namespace Navbar {

    void Bootstrap() {
        AuthState::Register("Navbar", State::Auth);

        Profile::RegisterLink();
    }

    void Destroy() {
        Profile::EraseLink();
    }

    namespace State {

        void Auth(const char* arg){
            json jDat = json::parse(arg);

            switch(jDat["action"].get<AuthState::AUTHSIGNAL>()){
                case AuthState::AUTHSIGNAL::LOGIN:

                    if(!jDat["failure"].get<bool>())
                        Profile::Events::SetText(safestr::duplicate(jDat["name"].get<string>().c_str()));

                    break;
                case AuthState::AUTHSIGNAL::LOGOUT:

                    Profile::Events::SetText(safestr::duplicate("Profilo"));

                    break;
            }

            safeptr::free_block(arg);
        }
    }

}