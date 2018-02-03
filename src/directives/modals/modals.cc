#include <iostream>
#include <json.hpp>

#include "modals.h"
#include "modals.hjs"

#include "auth-modal/auth-modal.h"
#include "chat-modal/chat-modal.h"

#include "common/web-ui/web-ui.h"
#include "common/logger/logger.h"

using json = nlohmann::json;
using namespace std;
using namespace WebUI;

namespace Modal {

    namespace Events {

        void ShowModalByRef(const string& argc) {
            log_details("Modals::Show", argc);

            const string js_hide_modal = "window.showModal('" +
                                            argc +
                                          "')";

            WebUI::Execute(js_hide_modal);
        }

        void HideModalByRef(const string& argc) {
            log_details("Modals::Hide", argc);

            const string js_show_modal = "window.hideModal('" +
                                            argc +
                                          "')";

            WebUI::Execute(js_show_modal);
        }
        
    }

    void Bootstrap() {
        log_details("Modals", "Bootstrap");

        WebUI::Execute(_src_directives_modal_modal_js);

        AuthModal::RegisterModal();
        ChatModal::RegisterModal();
    
    }

    void Destroy() {
        log_details("Modals", "Destroy");

        AuthModal::EraseModal();
        ChatModal::EraseModal();

    }


}