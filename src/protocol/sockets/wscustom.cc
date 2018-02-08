
#include <iostream>
#include <thread>
#include <thread>

#include "wscustom.h"

#include "common/logger/logger.h"
#include "env.h"

using json = nlohmann::json;
using WebSocket = easywsclient::WebSocket;
using namespace std;

/**
 * @brief Definizione protocollo di comunicazione Websocket
 * @file wscustom.cc
 */

/*
    Next:
        - reconnect
        - better error handling
        - Mutex buffer, computing, channel (?)
        - Boost & async event driven (Asio)
*/

namespace ws {
 
    void Socket::ThreadMain(){

        // creazione di un canale websocket (vedi libreria easywsclient)
        // viene effettuata nel thread così il thread UI non ne risente
        //   per i tempi di handshaking
        this->channel = WebSocket::from_url(this->path);

        // Abilitazione socket in modalità computing
        this->is_computing = true;

        // this->channel implica il controllo sul fatto che non vi siano errori di connessione
        // e che il canale non sia stato chiuso dal server.
        // Per errori si intende che:
        //  - il canale di comunicazione sia stato creato
        //  - il nodo (endpoint) esista
        while(this->channel && this->channel->getReadyState() != WebSocket::CLOSED) {

            if(this->is_computing) {

                // Se buffer pieno o messaggio non inviato
                if(this->buffer.content.size() > 0 && !this->buffer.is_send) { 
                    // Invia messagio e setta flag inviato sul buffer
                    this->channel->send(this->buffer.content);
                    this->buffer.is_send = true;
                } else
                    // Alla risposta svuota il buffer se non è ancora stato fatto
                    this->reset();
                
                // Dispatch ricezione risposta. Utilizzo lamba function condividento il contesto
                this->channel->dispatch([this](const string& str_response) {
                    
                    BaseResponse response(str_response);

                    if(response.ok)
                        this->onmessage(response.content);
                    else
                        this->onerror(response.error);
                });

            }

            // Effettua poll a livello più lento e ignora operazioni read/write
            this->channel->poll(this->is_computing ? SOCKET_ACTIVE_POLL : SOCKET_INACTIVE_POLL);
        }

        // Il canale è stato terminato in modo inaspettato e non richiesto dall'utente
        if(this->is_computing){
            this->onerror("Bad connection");
        }

    }

    void Socket::pause() {
        this->is_computing = false;
    }

    void Socket::resume() {
        this->is_computing = true;
    }

    void Socket::reset() {
        this->buffer.content  = "";
        this->buffer.is_send = false;
    }

    void Socket::setBuffer(BaseRequest& request){
        this->reset();

        this->buffer.content = request.serialize();
    }

    Socket::~Socket(){

        if(this->channel){
            this->channel->close();
            
            if(this->watcher.joinable()) 
                this->watcher.join();

            delete this->channel;
                   this->channel = 0;
        }

    }

    Socket::Socket( const std::string& node, 
                    void (*onmessage)(const std::string message), 
                    void(*onerror)(const std::string error)) {

        this->path = "ws://" + SERVER_HOST + "/" + node;

        this->onmessage = onmessage;
        this->onerror = onerror;

        this->reset();
        this->is_computing = true;

        this->watcher = std::thread(&Socket::ThreadMain, this);
        this->watcher.detach();
        
    }
}
