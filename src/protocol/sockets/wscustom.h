#ifndef PROTOCOL_SOCKETS_WSCUSTOM_H
#define PROTOCOL_SOCKETS_WSCUSTOM_H

#include <thread>
#include "easywsclient.h"
#include "models/socket/socket.h"

/**
 * @brief Interfaccia per protocollo di comunicazione Websocket
 * @file wscustom.h
 */

/** Spazio dei nomi per protocollo di comunicazione Websocket che estende easywsclient */
namespace ws{

    /**
     * "Buffer" su cui vengono scambiati i dati per effettuare la comunicazione socket.
     * Per garantire il corretto funzionamento, è consigliato effettuare un controllo
     * esclusivo sugli accessi per evitare che due consumatori scrivano contemporaneamente 
     * più messaggi sullo stesso canale e vengano così mischiate o non gestite in modo 
     * corretto le comunicazioni.
     */
    typedef struct socket_buff {
        /**
         * Parametro che segnala la presenza di un messaggio nel buffer 
         * e di conseguenza si attende una risposta al poll successivo
         * prima di resettare questo valore.
         */
        bool is_send;
        std::string content; /**< Contenuto da inviare sul canale socket di comunicazione */
    } WsBuffer;



    /**
     * Interfaccia classe Socket che estende il protocollo di comunicazion WebSocket
     * della libreria easywsclient
     */
    class Socket {

        private:
            WsBuffer buffer; /**< Buffer data per channel*/
            std::string path; /**< URL per la connessione del websocket */

            /**
             * Determina se il websocket è attivo. 
             * Non implica la chiusura del canale 
             */
            bool is_computing;

            /** 
             * Puntatore all'oggetto di tipo canale webscoket
             * messo a disposizione dalla libreria easywsclient
             */
            easywsclient::WebSocket::pointer channel;

             /**
              * Thread incaricato della gestione del canale. 
              * Fare riferimento a ThreadMain
              */
            std::thread watcher; 

            /** Puntatore a funzione (callback) per notificare la ricezione di un messaggio valido */
            void (*onmessage)(const std::string message); 

            /** Puntatore a funzione (callback) per notificare errori o messaggio invalido */
            void (*onerror)(const std::string error);

            void reset(); /**< Metodo per ripristinare il buffer al suo valore di default */
            
            /**
             * Metodo in esecuzione dal thread watcher.
             * Incaricato della gestione del canale e 
             * contiene il main loop del canale di comunicazione
             * aperto per effettuare polling.
             */
            void ThreadMain();

        public:
            /** 
             * Costruttore del canale.
             *
             * @param node Endpoint di collegamento per lo scambio dei dati
             * @param onmessage Puntatore a funzione callback success
             * @param onerror Puntatore a funzione callback errors 
             */
            Socket(const std::string& node, void (*onmessage)(const std::string message), void(*onerror)(const std::string error));
            
            /** 
             * Distruttore del canale.
             */
            ~Socket();

            /** Metodo per riprendere l'esecuzione a seguito di una pausa */
            void resume();

            /** Metodo per mettere in pausa l'esecuzione del polling */
            void pause();

            /** 
             * Metodo per impostare il contenuto del buffer con il contenuto della
             * richiesta in formato JSON serializzato string
             *
             * @param request Oggetto di tipo base request contenente le informazioni
             * informazioni e il contenuto della richiesta.
             */
            void setBuffer(const BaseRequest& request);
    };
}

#endif