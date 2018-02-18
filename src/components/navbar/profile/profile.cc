#include <iostream>
#include <json.hpp>

#include "profile.h"
#include "profile.js.h"

#include "common/web-ui/web-ui.h"
#include "common/logger/logger.h"

#include "states/auth-state/auth-state.h"

using json = nlohmann::json;
using namespace std;
using namespace WebUI;
using namespace States;

/**
 * @brief Definizione Navbar/Profile, link profilo barra di navigazione
 * @file profile.cc
 */

namespace Navbar {
    
    namespace Profile {

        namespace Events {

            inline void Disconnect(const std::string& args){
                log_details(TAG::CMP, "Navbar::Profile::Disconnect", args);
                AuthState::Logout();
            }

            void SetText(const std::string text) {
                log_details(TAG::CMP, "Navbar::Profile::SetText", text);

                const string js_nav_link = "window.navbar.ProfileLink.setText('" + 
                                                text +
                                            "')";

                WebUI::Execute(js_nav_link);
            }

        }

        void RegisterLink(){
            log_base(TAG::CMP, "Navbar::Profile::RegisterLink", "");

            WebUI::Execute(_src_components_navbar_profile_profile_js);

            WebUI::Register("Navbar::Profile::Disconnect", Events::Disconnect);
        }

        void EraseLink() {
            log_base(TAG::CMP, "Navbar::Profile::EraseLink", "");
        }

    }

}