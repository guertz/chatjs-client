#ifndef COMMON_WEB_UI_WEB_UI_H
#define COMMON_WEB_UI_WEB_UI_H

#include <map>
#include <webview.h>

/**
 * @brief Interfaccia Funzioni di supporto e metodi elementari e creazione della webview
 * @file web-ui.h
 */

/** Funzioni di supporto e metodi elementari e creazione della webview */
namespace WebUI {

    /** Definizione tipo di dato struct webview in Webview.
     *  Composta dagli attributi:
     *  + **title**: Titolo della finestra
     *  + **url**: Url in fomato data:text/html,...html
     *  + **width**
     *  + **height**
     *  + **resizable**
     *  + **debug**
     */
    typedef struct webview Webview;

    /** 
     * Definizione della struttura map ad ogni stringa un puntatore a funzione.
     */
    typedef std::map<std::string , void(*)(const std::string& argc)> Methods; 

    /**
     * Inserisce nella mappa dei metodi ::Methods un evento di callback.
     *
     * @param[in] cb_name string contenente il nome di riferimento all'evento di callback
     * @param[in] cb_fn Puntatore a funzione relativo all'evento di callback da invocare
     * 
     */
    void Register(std::string cb_name, void (*cb_fn)(const std::string&));
    
    /**
     * Metodo per la creazione della finestra webview.
     * <a href="https://github.com/zserge/webview">Github zserge/webview</a> 
     *
     * @return ::Webview
     */
    Webview* Create();

    /**
     * Metodo che inizializza la webview con gli script e stili di basi (assets).
     * Includendo le risorse in parti del codice C++ previene la modifica di
     * quest'ultimo da parte di malintenzionati
     */
    void Inject();

    // TODO: Better method names + funzionalità di logging
    /**
     * Metodo helper interno per eseguire sulla webview le istruzioni JavaScript
     * passate come parametro. Si limita semplicamente a leggere il contenuto 
     * dal puntatore ad arrey di caratteri e ad eseguirlo tramite la funzione
     * di libreria webview_eval. 
     *
     * @param[in] w Puntatore all'oggetto istanza Webview
     * @param[in] parsed_script Puntatore ad array di caratteri (codice js da eseguire)
     *
     */
    inline void Dispatch(Webview *w, const char *parsed_script );

    // TODO: Explain
    // Metodi di interfaccia per il metodo ::Execute
    // legge l'array con reinterpret_cast e invoca il
    // precedentemente definito metodo ::Dispatch
    inline void DispatchThread(Webview *w, void *voidPtrChar );
    
    
    /**
     * Metodo per inviare in modo arbitrario dati da eseguire sul thread UI principale.
     * A livello di API è un wrapper per la funzione di libreria webview_dispatch e
     * si appoggia al metodo ::Dispatch incaricato di eseguire il codice passato
     * come parametro
     *
     * @param[in] args Contenuto javascript da eseguire
     */
    void Execute(const std::string& args);

    /**
     * Metodo che viene ivocato a seguido della chiamata alla funzione
     * Javascript window.external.invoke() da parte della webview.
     *
     * La struttura JSON di riferimento è la seguente:
     * @include cb_fn.json
     *
     * Invoca la funzione identificata dal parametro 'fn' presente
     * nell'oggetto JSON deserializzato tramite il puntatore a funzione
     * mappato nella lista dei metodi di callback.
     *
     * @param[in] w Puntatore all'oggetto istanza Webview
     * @param[in] args Array di caratteri contenenti il buffer json serializzato
     */
    inline void JsHCallback(Webview *w, const char *args);


    // namespace Events {
    //     void OnResize(const char* args);
    // }
    

}

#endif