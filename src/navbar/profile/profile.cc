#include <iostream>
#include <json.hpp>

#include "profile.h"

#include "common/helpers/web_ui.h"
#include "common/helpers/helpers.h"

#include "providers/session/authstate.h"

using json = nlohmann::json;
using namespace std;
using namespace WebUI;
using namespace Helpers;

namespace Navbar {
    namespace Profile {

        void RegisterLink(){

            WebUI::Register("Navbar::Profile::Disconnect", Events::Disconnect);
        }

        void EraseLink() {

        }

        namespace Events {
            void Disconnect(const char* arg){
                AuthState::logout();
                safeptr::free_block(arg);
            }

            void SetText(const char* arg) {
                const char* js_action = js::compact(70 + strlen(arg), 3, 
                                            "window.navbar.profileLink.methods.setText('", 
                                                    arg,
                                                "')");

                webview_dispatch(   
                    WebUI::GetContext(), 
                    WebUI::Dispatch, 
                    safeptr::serialize(safestr::duplicate(js_action))
                );
            }
        }
    }

}