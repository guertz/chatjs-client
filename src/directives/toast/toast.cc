#include<iostream>
#include<json.hpp>

#include "toast.h"
#include "toast.hjs"

#include "common/web-ui/web-ui.h"
#include "common/helpers/helpers.h"

using json = nlohmann::json;
using namespace std;
using namespace WebUI;
using namespace Helpers;

namespace Toast {

    void Bootstrap(){

        WebUI::Execute(_src_directives_toast_toast_js);

    }

    namespace Events {
        void Show(const string& content){
            const string js_toast = "window.makeAToast('" +
                                        content +
                                    "')";

            WebUI::Execute(js_toast);
        }
    }
}