#include "app.h"

#include "directives/navbar/navbar.h" 
#include "directives/modals/modals.h"
#include "pages/chat-list/chat-list.h"
#include "pages/chat-details/chat-details.h"

#include "common/web-ui/web-ui.h"
#include "common/helpers/helpers.h"
#include "common/logger/logger.h"

#include "providers/chats/chats.h"
#include "states/auth-state/auth-state.h"

using namespace WebUI;
using namespace Helpers;
using namespace States;

extern char _binary_src_app_app_js_start[];

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
    void Init() { // < TODO: static
        // ChatState::Bootstrap();
        AuthState::Bootstrap();
        
        Navbar::Bootstrap();
        Modal::Bootstrap();

        // ChatList::Bootstrap();
        // ChatDetails::Bootstrap();
    }

    namespace Events {

        void Ready(const char *args) {

            log_base("App", "App event created");
            Init();

            safeptr::free_block(args);
        }

    }


    void Bootstrap() {
        WebUI::Register("App::Ready", Events::Ready);

        WebUI::Execute(
                safeptr::parse_asset(
                    _binary_src_app_app_js_start)
            );

    }

    void Destroy() {

        Navbar::Destroy();
        Modal::Destroy();
        
    }
}