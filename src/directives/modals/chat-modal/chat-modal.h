#ifndef DIRECTIVES_MODALS_CHAT_MODAL_CHAT_MODAL_H
#define DIRECTIVES_MODALS_CHAT_MODAL_CHAT_MODAL_H

namespace Modal {

   /**
    * Modale che mostra una lista di utenti con cui iniziare una chat.
    */
    namespace ChatModal {

       /**
        * Metodo di inizializzazione del modale
        */
        void RegisterModal();
       /**
        * Metodo di distruzione del modale
        */
        void EraseModal();
        
       /**
        * Spazio dei nomi in cui vengono registrati gli eventi che vanno ad interagire
        * sulla finestra. Vengono ragruppati gli eventi che provengono da entrambe le
        * direzioni ovvero:
        * + Invocazione di metodi C++ che richiamano funzioni Javascript
        * + Invocazioni dal Javascript a metodi C++
        */
        namespace Events {
 
           /**
            * Metodo invocato da JavaScript che notifica la selezione della persona 
            * con cui iniziare la chat.
            * Di seguito e riportata la struttura dati ricevuta dalla funzione
            *
            * @include modals/chat-modal-submit.json
            *
            * @param[in] argc Parametri della chiamata JS in formato JSON serialized
            * @return void
            */
            void NewChatOpen(const std::string& argc);

            /** Metodo per mostrare il modale */
            void Show();

            // TODO: Separete events, from method
            /** Metodo per nascondere il modale */
            void Close(const std::string& args);
            void Hide();

        }

       /**
        * Spazio dei nomi relativo agli eventi generati da callbacks. Esempi 
        * sono lo stato dell'autenticazione utente.
        */
        namespace State {
           
           /** 
            * Metodo che ascolta in tempo reale eventi riguardanti lo stato della
            * lista di chat attive come cambiamenti del contenuto di quest'ultima.
            * Dopo essere stato registrato viene notificato dal corrispondente provider
            * di eventuali cambiamenti di stato quali azioni di "inizio" di una nuova chat
            *
            * @include modals/chats/new-chat-response.json
            *
            * @param[in] argc Stringa json serializzata contenente le informazioni riguardanti
            * il cambio di stato
            */
            void Users();
                       
        }
    }
}

#endif