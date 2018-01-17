#include <iostream>
#include <json.hpp>
#include <assert.h>

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

// Simboli di riferimento per leggere il contenuto presente nei file binari 
// generati tramite il comando ld e contenti le risorse dell'applicazione 
// quali stile CSS, logica JS, struttura HTML.
//
// Questi file sono successivamente inclusi nella fase di compilazione come
// file oggetto.
//
// Il nome della variabile (simbolo) dipende fortemente dalla posizione del 
// file e da dove viene eseguito il comando ld

extern char _binary_assets_index_html_start[]; /**< Riferimento inizio file index.html markup scheletro app */

extern char _binary_assets_appinit_js_start[]; /**< Riferimento inizio file appinit basic js bindings */

extern char _binary_assets_style_css_start[]; /**< Riferimento inizio file style.css stile personalizzato */

extern char _binary_assets_stylew3_css_start[]; /**< Riferimento inizio file stylew3.css stile css base */

namespace WebUI {

    static Webview webview; /** Oggetto del tipo di dato webview */
    static Methods callbacks; /** Mappa in cui vengono memorizzate le associazioni 
                                    nome <=> puntatore a funzione (callback)*/

    void Register(string callback_name, void (*callback_fn)(const char *)){
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
        
        if (fn_itr != callbacks.end())
            fn_itr->second(safestr::duplicate(function.at("params").dump().c_str())); // Se iteratore valido invoco la funzione duplicato il buffer

            // jArgs["params"].dump().c_str() [duplicate]
            // unify js code
            // unify c++ code

            
        // safeptr(args...)
    }

    Webview* Create(){
        string prefix = "data:text/html,"; // Prefisso necessario quando viene caricato il file HTML 
                                           // tramite stringa e non da file su disco. 
                                           // Per dettagli fare riferimento alla libreria webview
        
        const char* kPrefix = safestr::duplicate(prefix.c_str());
        const char* const BLOB = reinterpret_cast<const char* const>(&_binary_assets_index_html_start);
        char* html = safestr::bufferizable(strlen(kPrefix)+strlen(BLOB));

                strcat(html, kPrefix);
                strcat(html, BLOB); // concateno il codice html con il prefisso 
        
        webview.url = safestr::duplicate(html);
        webview.title = "Chat.js";
        
        webview.width = 800;
        webview.height = 600;
        webview.resizable = 0; // disabilito il resize della finestra  
                               // provvisoriamente per motivi di 
                               // responsiveness

        // TODO: check success or exception (assert)
        webview_init(&webview); // Funzione per inizializzare oggetto webview
        webview.external_invoke_cb  = JsHCallback; // Registro il callback C++ al metodo invoke javascript
        
        WebUI::Register("WebUI::Log", WebUI::Log);

        safeptr::free_block(kPrefix);
        safeptr::free_block(html);

        return &webview;
    }

    // TODO: Optimizable params, w already known
    void Dispatch(Webview* w, void* voidPtrChar){

        char* args = safeptr::deserialize(voidPtrChar);

        webview_eval(w, args); // Momento in cui il codice javascript viene effettivamente
                               // valutato ed eseguito nel contesto della webview
        
        // safeptr::free_block(deserialized);
    }

    void Inject() {
        
        // TODO: tipo dei puntatori
        const char* const appinit = reinterpret_cast<const char* const>(&_binary_assets_appinit_js_start);

        const char* const stylew3 = reinterpret_cast<const char* const>(&_binary_assets_stylew3_css_start);

        // Required later
        const char* const _c_style = reinterpret_cast<const char* const>(&_binary_assets_style_css_start);
        unsigned char* const _u_style = reinterpret_cast<unsigned char* const>(&_binary_assets_style_css_start);
        
        // workaround for multiline css sheet
        const char* const style   = Base64::Encode(_u_style, strlen(_c_style), false).c_str();

        // anche il css deve essere eseguito da una sorta di funzione javascript 
        const char* kInjectableStyle = js::compact(strlen(style) + 25, 3, "stylify(true, '", style, "')");
        const char* kInjectableStylew3 = js::compact(strlen(stylew3) + 25, 3, "stylify(false, '", stylew3, "')");

        const char* appready = js::compact(15, 1, "appready()");

        webview_dispatch(&webview,Dispatch, js::prepare(appinit));
        webview_dispatch(&webview,Dispatch, js::prepare(kInjectableStylew3));
        webview_dispatch(&webview,Dispatch, js::prepare(kInjectableStyle));
        webview_dispatch(&webview,Dispatch, js::prepare(appready));
        
        // safeptr::free_block(style);
        safeptr::free_block(kInjectableStyle);
        safeptr::free_block(kInjectableStylew3);
        safeptr::free_block(appready);

    }

    void Execute(const char* const action) {

        webview_dispatch(
            &webview,
            Dispatch,
            js::prepare(action)
        );
    }

    // TODO: const to prevent setting changes
    Webview* GetContext(){
        return &webview;
    }

    // TODO: Useless?
    //       add firebug
    //       debug in both data structure (quelle 2 lì web, web.priv?)
    void Log(const char* argl) {
        json log_data = json::parse(argl);

        log_csl(
                log_data.at("attr").get<string>().c_str(),
                log_data.at("log_msg").get<string>().c_str()
            );

        safeptr::free_block(argl);

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