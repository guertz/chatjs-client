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

#include "common/helpers/helpers.h"
#include "common/base64/base64.h"
#include "common/logger/logger.h"

using json = nlohmann::json;
using namespace std;
using namespace Helpers;

#ifdef DEBUG_MODE
#define FIRE_BUG "<script type='text/javascript' src='/local/path/to/firebug-lite.js'></script>"
#endif

namespace WebUI {

    static Webview webview; /** Oggetto del tipo di dato webview */
    static Methods callbacks; /** Mappa in cui vengono memorizzate le associazioni 
                                    nome <=> puntatore a funzione (callback)*/

    void Register(string callback_name, void (*callback_fn)(const string&)){
        callbacks[callback_name] = callback_fn;
    }

    /**
     * Metodo che viene chiamato a seguido della chiamata alla funzione
     * JavaScript invoke.
     * È incaricato di cercare il puntatore a funzione mappato sull'oggetto map di tipo (::Methods)
     * e registrato tramite il metodo (::Register) e nel caso fosse presente, invoca quest'ultima
     * funzione.
     *
     * Questa funzione viene viene registrato nel metodo ::Create come parametro external_invoke_cb
     * della struttura dati ::Webview
     *
     * Non è necessario definirla a livello di interfaccia dato che non è necessario
     * che sia visibile agli altri file o parti che compongono l'applicazione
     *
     * @param[in] w Puntatore all'oggetto istanza Webview
     * @param[in] args Array di caratteri contenenti il buffer json serializzato
     *                 contenente nome della funzione da invocare e parametri da
     *                 passare a quest'ultima
     * @return void
     */
    void JsHCallback(Webview *w, const char *args) {

        json function = json::parse(args); /** oggetto json deserializzato */

        Methods::iterator fn_itr = callbacks.find(function.at("fn")); /** Iteratore dell'oggetto map specializzato
                                                                    dal tipo di dato Methods che rappresenta
                                                                    l'oggetto contenente il puntatore a funzione */
        
        // TODO: Strict cast to struct from json to check structure?
        if (fn_itr != callbacks.end())
            fn_itr->second(function.at("params").dump()); // Se iteratore valido passo la stringa serializzata

        // delete args
    }

    Webview* Create() {
        const string prefix = "data:text/html," + _src_assets_index_html;  // Prefisso necessario quando viene caricato il file HTML 
                                                 // tramite stringa e non da file su disco. 
                                                 // Per dettagli fare riferimento alla libreria webview


        webview.url = prefix.c_str();
        webview.title = "Chat.js";
        
        webview.width = 800;
        webview.height = 600;
        webview.resizable = 0; // disabilito il resize della finestra  
                               // provvisoriamente per motivi di 
                               // responsiveness

        webview.external_invoke_cb  = JsHCallback; // Registro il callback C++ al metodo invoke javascript

        // TODO: check success or exception (assert)
        webview_init(&webview); // Funzione per inizializzare oggetto webview
        
        
        WebUI::Register("WebUI::Log", WebUI::Log);

        return &webview;
    }

    void Dispatch(Webview* w, void* voidPtrChar){

        char* args = safeptr::deserialize(voidPtrChar);

        webview_eval(w, args); // Momento in cui il codice javascript viene effettivamente
                               // valutato ed eseguito nel contesto della webview
        // TODO:
        // safeptr::free_block(deserialized || voidPtrChar);
    }

    void Inject() {
        
        const string style_w3   = "stylify(false, '" +
                                    _src_assets_w3_css +
                                "')"; 

        // workaround for multiline css sheet
        const string style64   = Base64::Encode(  
                                    reinterpret_cast<unsigned char* const>(safestr::duplicate(_src_assets_style_css.c_str())), 
                                    _src_assets_style_css.size(),
                                    false);

        // anche il css deve essere eseguito da una sorta di funzione javascript 
        const string style = "stylify(true, '" + style64 + "')";

        const string appready = "appready()";

        log_details("WebUI", "Pushing assets code");
        log_pedantic("WebUI", "\t#Deploy appinit.js");
        
        Execute(_src_assets_appinit_js);
        log_pedantic("WebUI", "\t#Complete appinit.js");

        log_pedantic("WebUI", "\t#Deploy styleW3.css");
        Execute(style_w3);
        log_pedantic("WebUI", "\t#Complete styleW3.css");

        log_pedantic("WebUI", "\t#Deploy style.css");
        Execute(style);
        log_pedantic("WebUI", "\t#Complete style.css");

        log_pedantic("WebUI", "\t#Deploy appready.js");
        Execute(appready);
        log_pedantic("WebUI", "\t#Complete appready.js");

        log_details("WebUI", "Completed assets push");

    }

    void Execute(const char* const args){
        // Dispatch distrugge dopo?
        webview_dispatch(
            &webview,
            Dispatch,
            js::prepare(args)
        );
    }

    void Execute(const string& args) {

        // TODO: il puntatore ad action viene distrutto automaticamente non appena
        //       string action esce fuori dallo scope attuale
        Execute(args.c_str());

    }

    // Set debug filed + firebug
    void Log(const string& argl) {
        json log_data = json::parse(argl);

        log_csl(
                log_data.at("attr").get<string>(),
                log_data.at("log_msg").get<string>()
            );
    }

    // namespace Events {
    //     // do same thing as log
    //     // has it been registered somewhere?
    //     void OnResize(const char* args){
    //         // json jArgs = json::parse(args);

    //         // cout<<jArgs["params"].dump()<<endl;
    //         // safeptr::free_block(args);
    //     }
    // }
}