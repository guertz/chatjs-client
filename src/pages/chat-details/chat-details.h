#ifndef PAGES_CHAT_DETAILS_CHAT_DETAILS_H
#define PAGES_CHAT_DETAILS_CHAT_DETAILS_H

/**
 * @brief Interfaccia pagina ChatDetails in cui viene visualizzata la chat attiva
 * @file chat-details.h
 */

/** Interfaccia pagina ChatDetails in cui viene visualizzata la chat attiva */
namespace ChatDetails {

   /**
    * Spazio dei nomi in cui vengono registrati gli eventi che vanno ad interagire
    * sulla finestra.
    */
    namespace Events {
       /**
        * Handler di evento JavaScript che notifica l'invio di un messaggio
        * tramite il form.
        * Di seguito e riportata la struttura dati ricevuta dalla funzione
        *
        * @include pages/chat-details/submit.json
        *
        * @param[in] args Parametri della chiamata JS in formato JSON serialized
        */
        inline void Submit(const std::string& args);
    }

    /** Metodo per inizializzare il componente */
    void Bootstrap();

    /** Metodo per distruggere il componente */
    void Destroy();
    
   /**
    * Spazio dei nomi relativo agli eventi generati da callbacks. Esempi 
    * sono lo stato dell'autenticazione utente.
    */
    namespace State {
       /** 
        * Metodo che ascolta in tempo reale eventi riguardanti lo stato della
        * chat corrente (selezionata e attiva) come invio/ricezione messaggi.
        */
        inline void Chat();
    }
}

#endif