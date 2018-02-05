#ifndef DIRECTIVES_MODALS_AUTH_MODAL_AUTH_MODAL_H
#define DIRECTIVES_MODALS_AUTH_MODAL_AUTH_MODAL_H

namespace Modals {

   /**
    * Modale che permette ad un utente di autenticarsi.
    * Per maggiore dettagli sulla struttura fare riferimento a components.md
    * Viene mostrato all'avvio della app e a seguito della disconnessione
    * dell'utente. La schermata di autenticazione si presenta come un
    * semplice form in cui l'utente deve inserire il proprio ID
    */
    namespace AuthModal {

       /**
        * Spazio dei nomi in cui vengono registrati gli eventi che vanno ad interagire
        * sulla finestra.
        */
        namespace Events {

           /**
            * Handler di evento JavaScript che notifica l'invio dei dati del form di
            * autenticazione (submit).
            * Di seguito e riportata la struttura dati ricevuta dalla funzione
            *
            * @include modals/auth-modal-submit.json
            *
            * @param[in] argc Parametri della chiamata JS in formato JSON serialized
            *
            */
           inline void Submit(const std::string& argc);

           /**
            * Metodo che agisce su l'interfaccia e riporta il form al suo 
            * stato di default.
            */
            void Reset();

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
            * Metodo che ascolta in tempo reale eventi riguardanti l'autenticazione.
            * Dopo essere stato registrato viene notificato dal corrispondente provider
            * di eventuali cambiamenti di stato quali azioni di login e di logout
            */
            inline void Auth();
        }

        /**
         * Spazio dei nomi in cui vengono raggruppati metodi relativi
         * ad eventi generati dallo state di autenticazione
         */
        namespace AuthMethods {

            /** Metodo che viene invocato per notificare l'avvenuto login con successo */
            inline void OnLoginSuccess();

            /** Metodo che viene invocato per notificare l'avvenuto login con errori */
            inline void OnLoginErrors();

            /** Metodo che viene invocato per notificare l'azione di logout */
            inline void OnLogout();
        }
    }
}

#endif