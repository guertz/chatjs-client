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

namespace App {

    /** 
     * Metodo interno di inizializzazione del componente.
     * Viene invocato dopo che le risorse sono state
     * caricate per poter avviare i componenti (dato il fatto
     * che questi possono appoggiarsi a parti presenti nel JS)
     * Vengono attivate le seguenti parti:
     * + Servizi:
     *   - ChatState
     *   - AuthState
     * + Componenti:
     *   - Navbar
     *   - Modal
     *   - ChatList
     *   - ChatDetails 
     */
    void Init() {
        
        AuthState::Bootstrap();
        ChatState::Bootstrap();
        UsersState::Bootstrap();
        
        Navbar::Bootstrap();
        Modal::Bootstrap();
        Toast::Bootstrap();

        ChatList::Bootstrap();
        ChatDetails::Bootstrap();
        
    }

    namespace Events {

        void Ready(const string& args) {

            log_base("App", "App event created");
            Init();

        }

    }


    void Bootstrap() {
        WebUI::Register("App::Ready", Events::Ready);

        WebUI::Execute(_src_app_app_js);

    }

    void Destroy() {
        
        Navbar::Destroy();
        Modal::Destroy();

        // Toast::Destroy();
        // ChaList::Destroy();
        // ChatDetails::Destroy();

        ChatState::Destroy();
        UsersState::Destroy();
        AuthState::Destroy();
        
    }
}