#ifndef STATES_AUTH_STATE_AUTH_STATE_H
#define STATES_AUTH_STATE_AUTH_STATE_H

#include <map>

#include "models/socket/auth/auth-socket.h"

/**
 * @brief Interfaccia stato di autenticazione utenti
 * @file auth-state.h
 */

/** Spazio dei nomi relativo ai vari state dei dati */
namespace States {

    /** Stato di autenticazione utenti. */
    namespace AuthState {

        /** 
        * Definizione della struttura map che associa ad ogni stringa 
        * un puntatore a funzione. Viene utilizzata per gestire i componenti
        * che sottoscrivono ad ascoltare gli eventi di questo stato e a
        * notificare dei cambiamenti
        */
        typedef std::map<std::string, void(*)()> Subscribers;

        /**
        * Inserisce nella mappa dei subscribers AuthState::Subscribers un evento di callback.
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
         * Metodo per effettuare il login. 
         *
         * @param AUTH codice identificativo utente che effettua login
         */
        void Login(const std::string& AUTH);

        /** Metodo per effettuare logout dell'utente attualmente connesso */
        void Logout();
        
        /** 
         * Metodo per ottenere il tipo dell'ultima azione sullo stato di autenticazione utente 
         *
         * @return SIGNAL
         */
        AuthSocket::SIGNAL  getAuthAction();

        /** 
         * Metodo per ottenere l'utente connesso 
         *
         * @return User (vuoto e invalido by default or logout)
         */
        User getAuthUser();

        /**
         * Metodo per ritornare eventuali errori di autenticazione
         *
         * @return stringa con errori di autenticazione (vuota se tutto corretto) 
         */
        std::string getAuthError();

        /** 
        * Metodo per notificare cambiamenti di stato ai componenti che
        * hanno sottoscritto allo stato di autenticazione
        */
        inline void Notify();
        
        namespace AuthSocketMethods {

            /**
            * Metodo per gestire l'avvenuta ricezione nel corretto formato
            * a seguito di un azione di tipo AuthSocket::SIGNAL sul canale 
            * di comunicazione socket aperto.
            *
            * @param str_response Messaggio di risposta in formato JSON serializzato
            */
            inline void ResponseSuccess(const std::string str_response);

            /**
            * Metodo per gestire l'avvenuta ricezione di un messaggio di errore a 
            * seguito di un azione di tipo AuthSocket::SIGNAL sul canale 
            * di comunicazione socket aperto.
            *
            * @param str_error Messaggio di errore stringa testo
            */
            inline void ResponseError(const std::string str_error);

        }

    }
}

#endif