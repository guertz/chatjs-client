#include <iostream>

#include "app.h"
#include "app.js.h"

#include "components/navbar/navbar.h" 
#include "components/modals/modals.h"
#include "components/toast/toast.h"

#include "components/chat-list/chat-list.h"
#include "components/chat-details/chat-details.h"

#include "common/web-ui/web-ui.h"
#include "common/logger/logger.h"

#include "states/users-state/users-state.h"
#include "states/chats-state/chats-state.h"
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

            log_base(TAG::CMP, "App::Ready", args);
           
            AuthState::Bootstrap();
            ChatsState::Bootstrap();
            UsersState::Bootstrap();
            
            Navbar::Bootstrap();
            Modals::Bootstrap();
            Toast::Bootstrap();

            ChatList::Bootstrap();
            ChatDetails::Bootstrap();

        }

    }


    void Bootstrap() {
        log_base(TAG::CMP, "App::Bootstrap", "");

        WebUI::Register("App::Ready", Events::Ready);
        WebUI::Execute(_src_app_app_js);

    }

    void Destroy() {
        log_base(TAG::CMP, "App::Destroy", "");

        Navbar::Destroy();
        Modals::Destroy();

        // Toast::Destroy();
        ChatList::Destroy();
        ChatDetails::Destroy();

        ChatsState::Destroy();
        UsersState::Destroy();
        AuthState::Destroy();
        
    }
}