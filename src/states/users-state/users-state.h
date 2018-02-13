#ifndef STATES_USERS_STATE_USERS_STATE_H
#define STATES_USERS_STATE_USERS_STATE_H

#include "models/socket/users/users.h"

/**
 * @brief Interfaccia stato di autenticazione utenti
 * @file users-state.h
 */

/** Spazio dei nomi relativo ai vari state dei dati */
namespace States {

    /** Stato data lista utenti per iniziare chat. */
    namespace UsersState {

        /** 
        * Definizione della struttura map che associa ad ogni stringa 
        * un puntatore a funzione. Viene utilizzata per gestire i componenti
        * che sottoscrivono ad ascoltare gli eventi di questo stato e a
        * notificare dei cambiamenti
        */
        typedef std::map<std::string, void(*)()> Subscribers;

        /**
        * Inserisce nella mappa dei subscribers ::Subscribers un evento di callback.
        *
        * @param[in] cb_name string contenente il nome di riferimento all'evento di callback
        * @param[in] cb_fn Puntatore a funzione relativo all'evento di callback da invocare
        * 
        */
        void Register(std::string cb_name, void (*cb_fn)());

        /** Metodo per inizializzare il provider */
        void Bootstrap();

        /** Metodo per distruggere il provider */
        void Destroy();
    
        /** 
         * Metodo per ottenere la lista di utenti disponibili con cui iniziare una chat 
         *
         * @return stringa json serializzata utenti
         */
        const std::string& getSerializedList();

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
            void Auth();
        }
    }
}

#endif