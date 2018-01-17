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
        void Show(const char* argc){
            const char* js_action = js::compact(30 + strlen(argc), 3, 
                            "window.makeAToast('",
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