#include <iostream>
#include <map>
#include <json.hpp>
#include <cassert>
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
        const char* prefix = "data:text/html,";  // Prefisso necessario quando viene caricato il file HTML 
                                                 // tramite stringa e non da file su disco. 
                                                 // Per dettagli fare riferimento alla libreria webview

        const char* const BLOB = reinterpret_cast<const char* const>(&_binary_assets_index_html_start);
        char* html = safestr::bufferizable(strlen(prefix)+strlen(BLOB));

                strcat(html, prefix);
                strcat(html, BLOB); // concateno il codice html con il prefisso 
        
        webview.url = safestr::duplicate(html);
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

        safeptr::free_block(html);

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
        

        const char* const stylew3 = reinterpret_cast<const char* const>(&_binary_assets_stylew3_css_start);
        const char* js_style_w3   = js::compact(strlen(stylew3) + 25, 3, 
                                                    "stylify(false, '", 
                                                        stylew3, 
                                                    "')"); 

        // workaround for multiline css sheet
        const string style   = Base64::Encode(  
                                    reinterpret_cast<unsigned char* const>(&_binary_assets_style_css_start), 
                                    strlen(reinterpret_cast<const char* const>(&_binary_assets_style_css_start)),
                                    false);

        // anche il css deve essere eseguito da una sorta di funzione javascript 
        const string js_style = "stylify(true, '" + style + "')";

        const string appready = "appready()";

        // TODO webview Execute
        Execute(safeptr::parse_asset(
                _binary_assets_appinit_js_start));

        Execute(js_style_w3);
        Execute(js_style);
        Execute(appready);

        safeptr::free_block(js_style_w3);

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