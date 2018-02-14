#ifndef STATES_CHAT_STATE_CHAT_STATE_H
#define STATES_CHAT_STATE_CHAT_STATE_H

#include <map>

#include "models/chats/chats.h"
#include "models/socket/chat/chat-socket.h"
#include "models/socket/chats/chats-socket.h"

/**
 * @brief Interfaccia stato gestione chat
 * @file chats-state.h
 */

/** Spazio dei nomi relativo ai vari state dei dati */
namespace States {

    /** Spazio dei nomi relativo allo state per la gestione delle chat */
    namespace ChatsState {
        
        /** 
        * Definizione della struttura map che associa ad ogni stringa 
        * un puntatore a funzione. Viene utilizzata per gestire i componenti
        * che sottoscrivono ad ascoltare gli eventi di questo stato e a
        * notificare dei cambiamenti
        */
        typedef std::map<std::string, void(*)()> Subscribers;

        /**
        * Inserisce nella mappa dei subscribers un evento di callback per gli eventi 
        * globali dello stato delle chats.
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
         * Metodo per iniziare una nuova chat con l'utente di destinazione
         * passato come parametro.
         *
         * @param[in] user_dest
         */
        void StartAChat(const std::string user_dest);

        /**
         * Metodo per ottenere la lista delle chat attive in formato stringa
         * json serializzato
         *
         * @return string lista chat del formato ::Chats
         */
        const std::string getSerializedChats();

        /**
         * Imposta la chat attiva, ovvero quella aperta nel pannello di destra
         * all'interno dell'applicazione a quella identificata dal parametro 
         * passato.
         *
         * @param[in] reference Codice identificativo della chat da considerarsi
         * attiva (visualizzata dall'utente)
         */
        void setCurrentChat(const std::string reference);

        /** 
         * Metodo per controllare se la chat è stata selezionata
         *
         * @return bool valore che indica se ci sono chat attive (selezionate/visibili)
         */
        bool isCurrentChat();

        /**
         * Metodo per ottenere il codice identificativo di riferimento della chat
         * attualmente selezionata
         *
         * @return string Valore della chat attualmente selezionata
         */
        const std::string getCurrentChatRef();

        /**
         * Metodo per ottenere la i dettagli in formato string serializzata json
         * della chat attualmente selezionata.
         * Viene anche ritornata la lista dei messaggi come possibile vedere dalla
         * definizione della classe ::Chat
         *
         * @return string Dettagli della chat attualmente selezionata in formato
         * json serializzato
         */
        const std::string getCurrentChat();

        /*
         * Metodo per notificare cambiamenti di stato ai componenti che
         * hanno sottoscritto allo stato di chats. Eventi sono la creazione
         * di una nuova chat con un utente
         */
        inline void Notify();

        namespace ChatsSocketMethods {

            /**
            * Metodo per inizializzare una sessione sul canale websocket aperto
            * per utente passato come parametro nel corpo del messaggio.
            * Questo metodo viene utilizzato a seguito di un'azione di login
            *
            * @param AUTH identificativo utente
            */
            inline void InitChannelSession(const std::string& AUTH);

            /**
            * Metodo per terminare una sessione sul canale websocket aperto
            * per utente precedentemente loggato.
            * Questo metodo viene utilizzato a seguito di un'azione di logout
            */
            inline void CloseChannelSession();

            /**
            * Metodo per gestire l'avvenuta ricezione nel corretto formato
            * a seguito di un azione di tipo ChatsSocket::SIGNAL sul canale 
            * di comunicazione aperto.
            *
            * @param str_response Messaggio di risposta in formato JSON serializzato
            */
            inline void ResponseSuccess(const std::string str_response);

            /**
            * Metodo per gestire l'avvenuta ricezione di un messaggio di errore a 
            * seguito di un azione di tipo ChatsSocket::SIGNAL sul canale di 
            * comunicazione aperto.
            *
            * @param str_error Messaggio di errore stringa testo
            */
            inline void ResponseError(const std::string str_error);

        }

        /** Spazio dei nomi relativo ai metodi per la gestione delle singole chat */
        namespace ChatMethods {

            /**
            * Inserisce nella mappa dei subscribers un evento di callback per gli eventi 
            * globali dello stato delle singole chat come ad esempio la ricezione di un
            * nuovo messaggio
            *
            * @param[in] cb_name string contenente il nome di riferimento all'evento di callback
            * @param[in] cb_fn Puntatore a funzione relativo all'evento di callback da invocare
            * 
            */
            void Register(std::string cb_name, void (*cb_fn)());

            /**
             * Metodo per inviare un messaggio di testo sulla chat attualmente selezionata
             *
             * @param[in] text Contenuto del messaggio di testo da inviare 
             */
            void SendAMessage(const std::string text);

            /*
            * Metodo per notificare cambiamenti di stato alla chat attualmente selezionata
            * ai componenti che hanno sottoscritto a questo tipo di eventi tramite il metodo
            * States::ChatsState::ChatMethods::Register. 
            * Eventi sono la ricezione di un nuovo messaggio
            */
            inline void NotifyCurrent();

            namespace ChatSocketMethods {

                /**
                * Metodo per inizializzare una sessione sul canale websocket 
                * di riferimento creato a seguito dell'azione di inizio di
                * nuova chat con un utente.
                *
                * @param chat Oggeto ::Chat di riferimento contenente i dati
                * e le informazioni della chat sulla quale inizializzare
                * la sessione
                */
                inline void InitChannelSession(const Chat& chat);

                /**
                * Metodo per terminare una sessione sul canale websocket aperto
                * relativo a una particolare chat. 
                */
                // inline void CloseChannelSession();
                
                /**
                * Metodo per gestire l'avvenuta ricezione nel corretto formato
                * a seguito di un azione di tipo ChatSocket::SIGNAL sul canale 
                * di comunicazione aperto di una specifica chat.
                *
                * @param str_response Messaggio di risposta in formato JSON serializzato
                */
                inline void ResponseSuccess(const std::string str_response);

                /**
                * Metodo per gestire l'avvenuta ricezione di un messaggio di errore
                * a seguito di un azione di tipo ChatSocket::SIGNAL sul canale di 
                * comunicazione aperto di una specifica chat.
                *
                * @param str_error Messaggio di errore stringa testo
                */
                inline void ResponseError(const std::string str_error);

            }

        } 
    
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