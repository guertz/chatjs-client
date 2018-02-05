#ifndef DIRECTIVES_MODALS_CHAT_MODAL_CHAT_MODAL_H
#define DIRECTIVES_MODALS_CHAT_MODAL_CHAT_MODAL_H

namespace Modals {

   /**
    * Modale che mostra una lista di utenti con cui iniziare una chat.
    * Per maggiore dettagli sulla struttura fare riferimento a components.md
    * Viene mostrato a seguito di una richiesta da parte dell'utente autenticato
    */
    namespace ChatModal {

       /**
        * Spazio dei nomi in cui vengono registrati gli eventi che vanno ad interagire
        * sulla finestra.
        */
        namespace Events {
 
           /**
            * Handler di evento JavaScript che notifica la selezione della persona 
            * con cui iniziare la chat.
            * Di seguito e riportata la struttura dati ricevuta dalla funzione
            *
            * @include modals/chat-modal-submit.json
            *
            * @param[in] argc Parametri della chiamata JS in formato JSON serialized
            */
            inline void NewChatOpen(const std::string& argc);

            /** Metodo per mostrare il modale */
            void Show();

            /** Metodo per nascondere il modale */
            void Hide();

        }

        /** Metodo di inizializzazione del modale */
        void RegisterModal();

        /** Metodo di distruzione del modale */
        void EraseModal();
        

       /**
        * Spazio dei nomi relativo agli eventi generati da callbacks. Esempi 
        * sono lo stato dell'autenticazione utente.
        */
        namespace State {
           
           /** 
            * Metodo che ascolta in tempo reale eventi riguardanti lo stato della
            * lista di chat attive come cambiamenti del contenuto di quest'ultima.
            */
            inline void Users();
                       
        }
    }
}

#endif