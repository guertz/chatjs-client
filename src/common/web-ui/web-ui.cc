#include <iostream>
#include <map>
#include <json.hpp>
#include <cassert>

#include "assets/appinit.hjs"
#include "assets/index.hhtml"
#include "assets/style.hcss"
#include "assets/w3.hcss"

#define WEBVIEW_IMPLEMENTATION
#include <webview.h>

#include "web-ui.h"

#include "common/base64/base64.h"
#include "common/logger/logger.h"

using json = nlohmann::json;
using namespace std;

#ifdef WEBVIEW_DEBUG
#define FIRE_BUG "<script type='text/javascript' src='/local/path/to/firebug-lite.js'></script>"
#endif

/**
 * @brief Definizione Funzioni di supporto e metodi elementari e creazione della webview
 * @file web-ui.cc
 */
namespace WebUI {

    /** 
     * Oggetto del tipo di dato webview. 
     * Rappresenta l'interfaccia dell'applicazione ed ha tempo di vita
     * tutto il programma (**static**)
     */
    static Webview webview; 
    static Methods callbacks;

    void Register(std::string cb_name, void (*cb_fn)(const std::string&)) {
        log_C(TAG::CSL, "WebUI::Register", cb_name);

        callbacks[cb_name] = cb_fn;
    }

    Webview* Create() {

        log_B(TAG::CSL, "WebUI::Create", "");

        const string prefix = "data:text/html," + _src_assets_index_html;

        webview.url = prefix.c_str();
        webview.title = "Chat.js";
        
        webview.width = 800;
        webview.height = 600;
        webview.resizable = 0; // window resize disabled

        // Javascript => C++ Handler
        webview.external_invoke_cb  = JsHCallback; 

        // TODO: Firebug/Web inspector
        #ifdef WEBVIEW_DEBUG
            webview.debug = true;
        #endif

        // TODO: check success or exception (assert)
        webview_init(&webview);

        return &webview;
    }

    void Inject() {
        
        log_B(TAG::CSL, "WebUI::Inject", "[r] running");

        const string style_w3   = "stylify(false, '" +
                                    _src_assets_w3_css +
                                "')"; 

        // workaround for multiline css style sheet
        const string style64   = Base64::Encode(  
                                    reinterpret_cast<unsigned char* const>(
                                        const_cast<char*>(_src_assets_style_css
                                                            .c_str()
                                                        )
                                    ), 
                                    _src_assets_style_css.size(),
                                    false);

        // anche il css deve essere eseguito da una sorta di funzione javascript 
        const string style = "stylify(true, '" + style64 + "')";

        const string appready = "appready()";

        // Fixing gdk_threads queue
        log_C(TAG::CSL, "WebUI::Inject", "appinit.js");
        Dispatch(&webview, _src_assets_appinit_js.c_str());

        log_C(TAG::CSL, "WebUI::Inject", "w3.css");
        Dispatch(&webview, style_w3.c_str());

        log_C(TAG::CSL, "WebUI::Inject", "style.css");
        Dispatch(&webview, style.c_str());

        log_C(TAG::CSL, "WebUI::Inject", "appready.js");
        Execute(appready);

        log_B(TAG::CSL, "WebUI", "[c] completed");

    }

    inline void DispatchThread(Webview* w, void* voidPtrChar) {
        Dispatch(w, reinterpret_cast<const char*>(voidPtrChar));
    }

    inline void Dispatch(Webview* w, const char* parsed_script) {

        #ifdef DEBUG_MODE
        #ifndef WEBVIEW_DEBUG

            char* __parsed_script_part = new char[LOG_LEN];
            int   __parsed_script_size = strlen(parsed_script) < LOG_LEN ? 
                                            strlen(parsed_script) : LOG_LEN;
                strncpy(  __parsed_script_part, 
                          parsed_script, 
                          __parsed_script_size);

            if(strlen(parsed_script) > LOG_LEN) {
                __parsed_script_part[56] = '.';
                __parsed_script_part[57] = '.';
                __parsed_script_part[58] = '.';
                __parsed_script_part[59] = '\0';
            }

            string parsed_script_part(__parsed_script_part);

            log_C(TAG::CSL, "WebUI::Dispatch", parsed_script_part);

            assert(__parsed_script_part);
            // TODO: check i always deleted arrays when needed
            delete[] __parsed_script_part;
            __parsed_script_part = 0;

        #endif
        #endif

        // Evaluating code inside the webview main ui thread
        webview_eval(w, parsed_script);
        
        // TODO: pointers
    }

    void Execute(const std::string& args) {

        char *content = new char[args.size() +1];
              strncpy(content, args.c_str(), args.size() +1);

        webview_dispatch(
            &webview,
            DispatchThread,
            content
        );

        // TODO: pointers

    }

    inline void JsHCallback(Webview *w, const char *args) {

        /** Dati callback in formato JSON deserializzato */
        json function = json::parse(args); 

        log_C(TAG::CSL, "WebUI::JsHCallback", function.at("fn").get<string>());

        Methods::iterator fn_itr = callbacks.find(function.at("fn").get<string>());

        assert(fn_itr !=  callbacks.end());
        
        fn_itr->second(function.at("params").dump());

        // duplicate string instead of reference?
        // TODO: pointers
    }

}