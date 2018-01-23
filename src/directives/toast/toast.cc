#include<iostream>
#include<json.hpp>

#include "toast.h"

#include "common/web-ui/web-ui.h"
#include "common/helpers/helpers.h"

using json = nlohmann::json;
using namespace std;
using namespace WebUI;
using namespace Helpers;

namespace Toast {

    namespace Events {
        void Show(const string& content){
            const string js_toast = "window.makeAToast('" +
                                        content +
                                    "')";

            WebUI::Execute(content);
        }
    }
}