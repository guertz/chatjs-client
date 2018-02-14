#include<iostream>
#include<json.hpp>

#include "toast.h"
#include "toast.js.h"

#include "common/web-ui/web-ui.h"
#include "common/logger/logger.h"

using json = nlohmann::json;
using namespace std;
using namespace WebUI;

/**
 * @brief Definizione Toast, sistema di comunicazione notifiche 
 * @file toast.cc
 */

namespace Toast {

    namespace Events {
        void Show(const std::string& args){
            log_C(TAG::CMP, "Toast::Show", args);

            const string js_toast = "window.makeAToast('" +
                                        args +
                                    "')";

            WebUI::Execute(js_toast);
        }
    }


    void Bootstrap(){
        log_B(TAG::CMP, "Toast::Bootstrap", "");

        WebUI::Execute(_src_components_toast_toast_js);
    }
}