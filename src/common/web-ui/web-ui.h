#ifndef COMMON_WEB_UI_WEB_UI_H
#define COMMON_WEB_UI_WEB_UI_H

#include <map>
#include <webview.h>

/** Funzioni di supporto e metodi elementari e creazione della webview. */
namespace WebUI {

    // TODO: specificare da quali attributi è composta
    /** Definizione tipo di dato struct webview in Webview */
    typedef struct webview Webview;

    /** 
     * Definizione della struttura dati map che mappa ad ogni stringa un puntatore a funzione.
     */
    typedef std::map<std::string , void(*)(const std::string& argc)> Methods; 

    /**
     * Registra sull'oggetto di tipo mappa ::Methods il puntatore a
     * funzione e lo associa alla stringa
     *
     * param callback_name Stringa identificativa del puntatore a funzione relativo
     * al metodo passato come parametro.
     * param callback_fn Puntatore a funzione del metodo da invocare
     * @return void
     */
    void Register(std::string callback_name, void (*callback_fn)(const std::string&));
    
    /**
     * Metodo per la creazione della finestra webview.
     * Per maggiori informazioni sulle API è possibile fare riferimento a
     * <a href="https://github.com/zserge/webview">Github zserge/webview </a> 
     *
     * @return Webview*
     */
    Webview* Create();

    /**
     * Metodo per iniettare gli script e gli stili nella webview.
     * È stato adottato questo sistema: per poter distribuire il 
     * pacchetto in un singolo file ed evitare modifiche da parte
     * di malintenzionati della logica JS dell'applicazione
     *
     * @return void
     */
    void Inject();

    /**
     * Metodo helper per eseguire istruzioni JavaScript sulla webview.
     * È di supporto alla funzione webview_dispatch della libreria webview
     * e serve ad unificare e semplificare il sistema di dispatching che
     * che consente di eseguire funzioni Javascript in modo asincrono
     *
     * @param[in] w Puntatore all'oggetto istanza Webview
     * @param[in] voidPtrChar Puntatore void ad array di caratteria (stringa serializzata void)
     * contenente la stringa javascript da eseguire nel contesto della webview
     *
     * @return void
     *
     */
    void Dispatch(Webview *w, void *voidPtrChar );
    
    void Execute(const std::string& args);
    void Execute(const char* const args);

    void Log(const std::string& arg);

    // namespace Events {
    //     void OnResize(const char* args);
    // }
    

}

#endif