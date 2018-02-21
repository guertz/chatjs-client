#include <iostream>
#include <json.hpp>

#include "modals.h"
#include "modals.js.h"

#include "auth-modal/auth-modal.h"
#include "chat-modal/chat-modal.h"
#include "conn-modal/conn-modal.h"
#include "sign-modal/sign-modal.h"

#include "common/web-ui/web-ui.h"
#include "common/logger/logger.h"

using json = nlohmann::json;
using namespace std;
using namespace WebUI;

/**
 * @brief Definizione Modals, modale per iniziare una chat
 * @file modals.cc
 */

namespace Modals {

    namespace Events {

        void ShowModalByRef(const std::string& args) {
            log_base(TAG::CMP, "Modals::Show", args);

            const string js_hide_modal = "window.showModal('" +
                                            args +
                                          "')";

            WebUI::Execute(js_hide_modal);
        }

        void HideModalByRef(const std::string& args) {
            log_base(TAG::CMP, "Modals::Hide", args);

            const string js_show_modal = "window.hideModal('" +
                                            args +
                                          "')";

            WebUI::Execute(js_show_modal);
        }
        
    }

    void Bootstrap() {
        log_base(TAG::CMP, "Modals::Bootstrap", "");

        WebUI::Execute(_src_components_modal_modal_js);

        AuthModal::RegisterModal();
        ChatModal::RegisterModal();
        ConnModal::RegisterModal();
        SignModal::RegisterModal();

    }

    void Destroy() {
        log_base(TAG::CMP, "Modals::Destroy", "");

        AuthModal::EraseModal();
        ChatModal::EraseModal();
        ConnModal::EraseModal();
        SignModal::EraseModal();

    }


}