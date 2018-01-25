#include <iostream>
#include <json.hpp>

#include "modals.h"
#include "auth-modal/auth-modal.h"
#include "chat-modal/chat-modal.h"

#include "common/web-ui/web-ui.h"
#include "common/helpers/helpers.h"

using json = nlohmann::json;
using namespace std;
using namespace WebUI;
using namespace Helpers;

extern char _binary_src_directives_modals_modals_js_start[];

namespace Modal {

    void Bootstrap() {
        
        WebUI::Execute(
                safeptr::parse_asset(
                    _binary_src_directives_modals_modals_js_start)
            );

        AuthModal::RegisterModal();
        ChatModal::RegisterModal();
    
    }

    void Destroy() {

        AuthModal::EraseModal();
        // ChatModal::EraseModal();

    }

    namespace Events {

        void ShowModalByRef(const string& argc) {

            const string js_hide_modal = "window.showModal('" +
                                            argc +
                                          "')";

            WebUI::Execute(js_hide_modal);
        }

        void HideModalByRef(const string& argc) {

            const string js_show_modal = "window.hideModal('" +
                                            argc +
                                          "')";

            WebUI::Execute(js_show_modal);
        }
        
    }

}