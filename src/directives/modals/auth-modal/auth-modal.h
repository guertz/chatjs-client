namespace Modal {

   /**
    * Modale che permette ad un utente di autenticarsi.
    * Viene mostrato all'avvio della app e a seguito della disconnessione
    * dell'utente. La schermata di autenticazione si presenta come un
    * semplice form in cui l'utente deve inserire il proprio ID
    */
    namespace AuthModal {

       /**
        * Spazio dei nomi in cui vengono registrati gli eventi che vanno ad interagire
        * sulla finestra. Vengono ragruppati gli eventi che provengono da entrambe le
        * direzioni ovvero:
        * + Invocazione di metodi C++ che richiamano funzioni Javascript
        * + Invocazioni dal Javascript a metodi C++
        */
        namespace Events {

           /**
            * Metodo invocato da JavaScript che notifica l'invio dei dati del form di
            * autenticazione.
            * Di seguito e riportata la struttura dati ricevuta dalla funzione
            *
            * @include modals/auth-modal-submit.json
            *
            * @param[in] argc Parametri della chiamata JS in formato JSON serialized
            * @return void
            */
            void Submit(const char* argc);

           /**
            * Metodo che agisce su l'interfaccia e riporta il form al suo 
            * stato di default.
            *
            * @return void
            */
            void Reset();

            /** Metodo per mostrare il modale */
            void Show();

            /** Metodo per nascondere il modale */
            void Hide();

        }
        
       /**
        * Metodo di inizializzazione del modale
        */
        void RegisterModal();

       /**
        * Metodo di distruzione del modale
        */
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
            *
            * Formato json evento authstate con parametri base
            * @include auth/auth-base.json
            *
            * Formato json evento authstate con parametri login
            * @include auth/auth-extended.json
            *
            * @param[in] argc Stringa json serializzata contenente le informazioni riguardanti
            * il cambio di stato
            */
            void Auth(const char* argc);
        }

        /**
         * Spazio dei nomi in cui vengono raggruppati metodi relativi
         * ad eventi generati dallo state di autenticazione
         */
        namespace AuthMethods {

            /**
             * Metodo che viene invocato per notificare l'avvenuto login con successo.
             */
            void OnLoginSuccess();

            /**
             * Metodo che viene invocato per notificare l'avvenuto login con errori.
             */
            void OnLoginErrors();

            /**
             * Metodo che viene invocato per notificare l'azione di logout
             */
            void OnLogout();
        }
    }
}