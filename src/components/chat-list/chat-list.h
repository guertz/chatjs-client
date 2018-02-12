#ifndef COMPONENTS_CHAT_LIST_CHAT_LIST_H
#define COMPONENTS_CHAT_LIST_CHAT_LIST_H
/**
 * @brief Interfaccia pagina ChatList in cui vengono visualizzate la chat aperte
 * @file chat-list.h
 */

/** Interfaccia pagina ChatList in cui vengono visualizzate la chat aperte */
namespace ChatList {

   /**
    * Spazio dei nomi in cui vengono registrati gli eventi che vanno ad interagire
    * sulla finestra.
    */
    namespace Events {
       /**
        * Handler di evento JavaScript che notifica la selezione della chat da
        * visualizzare.
        * Di seguito e riportata la struttura dati ricevuta dalla funzione
        *
        * @include pages/chat-list/user-selected.json
        *
        * @param[in] args Parametri della chiamata JS in formato JSON serialized
        */
        inline void UserSelected(const std::string& args);

       /**
        * Handler di evento JavaScript che notifica l'evento di click sul
        * bottone per iniziare una nuova chat
        * Di seguito e riportata la struttura dati ricevuta dalla funzione
        *
        * @param[in] args Parametri della chiamata JS in formato JSON serialized (vuoto)
        */
        inline void NewChat(const std::string& args);
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
        * Metodo che ascolta in tempo reale eventi riguardanti l'autenticazione.
        * Dopo essere stato registrato viene notificato dal corrispondente provider
        * di eventuali cambiamenti di stato quali azioni di login e di logout
        */
        inline void Auth();
       
       /** 
        * Metodo che ascolta in tempo reale eventi riguardanti lo stato della
        * lista chats come creazione di una nuova chat.
        */
        inline void Chats();

        /** 
        * Metodo che ascolta in tempo reale eventi riguardanti lo stato della
        * chat corrente (selezionata e attiva) come invio/ricezione messaggi.
        */
        inline void Chat();
    }
}

#endif