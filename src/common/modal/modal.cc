#include <iostream>
#include <json.hpp>

#include "common/helpers/web_ui.h"
#include "common/helpers/helpers.h"

#include "modal.h"
#include "modals/auth-modal/auth-modal.h"
#include "modals/chat-modal/chat-modal.h"

#include "providers/session/authstate.h"

using json = nlohmann::json;
using namespace std;
using namespace WebUI;
using namespace Helpers;

extern char _binary_src_common_modal_modal_js_start[];

namespace Modal {

    void Bootstrap() {
        
        WebUI::Execute(
                safeptr::parse_asset(
                    _binary_src_common_modal_modal_js_start)
            );

        AuthModal::RegisterModal();
        // ChatModal::RegisterModal();
    
    }

    void Destroy() {

        AuthModal::EraseModal();
        // ChatModal::EraseModal();

    }

    namespace Events {

        void ShowModalByRef(const char* argc) {

            const char* js_action = js::compact(50 + strlen(argc), 3, 
                                        "window.showModal('",
                                            argc,
                                        "')");

            webview_dispatch(   
                WebUI::GetContext(),
                WebUI::Dispatch, 
                safeptr::serialize(safestr::duplicate(js_action))
            );

            safeptr::free_block(argc);
            safeptr::free_block(js_action);
        }

        void HideModalByRef(const char* argc) {

            const char* js_action = js::compact(50 + strlen(argc), 3, 
                                        "window.hideModal('",
                                            argc,
                                        "')");

            webview_dispatch(   
                WebUI::GetContext(),
                WebUI::Dispatch, 
                safeptr::serialize(safestr::duplicate(js_action))
            );

            safeptr::free_block(argc);
            safeptr::free_block(js_action);
        }
        
    }

}