#include <iostream>

#include "app.h"
#include "app.hjs"

#include "directives/navbar/navbar.h" 
#include "directives/modals/modals.h"
#include "directives/toast/toast.h"

#include "pages/chat-list/chat-list.h"
#include "pages/chat-details/chat-details.h"

#include "common/web-ui/web-ui.h"
#include "common/logger/logger.h"

#include "states/users-state/users-state.h"
#include "states/chat-state/chat-state.h"
#include "states/auth-state/auth-state.h"

using namespace WebUI;
using namespace States;
using namespace std;

/**
 * @brief Definizione "Core" applicazione, gestisce i vari sotto-moduli.
 * @file app.cc
 */
namespace App {

    namespace Events {

        inline void Ready(const std::string& args) {

            log_pedantic("WebUI", "[c] App ready event");
            log_details("App", "Ready => Initializing!");
           
            AuthState::Bootstrap();
            ChatState::Bootstrap();
            UsersState::Bootstrap();
            
            Navbar::Bootstrap();
            Modals::Bootstrap();
            Toast::Bootstrap();

            ChatList::Bootstrap();
            ChatDetails::Bootstrap();

        }

    }


    void Bootstrap() {
        log_details("App", "Bootstrap");

        WebUI::Register("App::Ready", Events::Ready);
        WebUI::Execute(_src_app_app_js);

    }

    void Destroy() {
        log_details("App", "Destroy");

        Navbar::Destroy();
        Modals::Destroy();

        // Toast::Destroy();
        ChaList::Destroy();
        ChatDetails::Destroy();

        ChatState::Destroy();
        UsersState::Destroy();
        AuthState::Destroy();
        
    }
}