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

/**
 * @brief Definizione Modals, modale per iniziareuna chat
 * @file modals.cc
 */

namespace Modals {

    namespace Events {

        void ShowModalByRef(const std::string& args) {
            log_details("Modals::Show", args);

            const string js_hide_modal = "window.showModal('" +
                                            args +
                                          "')";

            WebUI::Execute(js_hide_modal);
        }

        void HideModalByRef(const std::string& args) {
            log_details("Modals::Hide", args);

            const string js_show_modal = "window.hideModal('" +
                                            args +
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