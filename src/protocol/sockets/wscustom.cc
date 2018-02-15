
#include <iostream>
#include <string>

#include "wscustom.h"

#include "common/uuid/uuid.h"
#include "common/logger/logger.h"

using json = nlohmann::json;
using WebSocket = easywsclient::WebSocket;
using namespace std;

/**
 * @brief Definizione protocollo di comunicazione Websocket
 * @file wscustom.cc
 */

/** Tempo espresso in ms di polling per socket in ascolto */
#define SOCKET_ACTIVE_POLL 300
/** Tempo espresso in ms di polling per socket dormiente */
#define SOCKET_INACTIVE_POLL 1000

#define SERVERHOST "137.74.196.151:8000"
#define LOCALHOST  "localhost:8000"

// Improve
//   - reconnect
//   - errors
//   - mutex on buffer, channel
//   - asio

namespace ws {
 
    void Socket::ThreadMain(){

        this->stopping = false;
        this->running = true;

        log_A(TAG::WSS, this->endpoint + "::ThreadMain", "[r] running");

        // creazione di un canale websocket (vedi libreria easywsclient)
        // viene effettuata nel thread così il thread UI non ne risente
        // per i tempi di handshaking

        #ifdef SERVER_REMOTE
            this->channel = WebSocket::from_url("ws://" + string(SERVERHOST) + "/" + this->endpoint);
        #else
            this->channel = WebSocket::from_url("ws://" + string(LOCALHOST) + "/" + this->endpoint);
        #endif
        
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
                    log_A(TAG::WSS, this->endpoint + "::ThreadMain", "[r] running send");
                } else {
                    if(this->buffer.is_send)
                        log_A(TAG::WSS, this->endpoint + "::ThreadMain", "[c] complete send");

                    // Pulizia del buffer, invio & poll completato almeno una volta
                    this->reset();
                     
                }

                // Dispatch ricezione risposta. Utilizzo lamba function condividento il contesto
                this->channel->dispatch([this](const string& str_response) {
                    BaseResponse response(str_response);
                    log_A(TAG::WSS, this->endpoint + "::ThreadMain::Dispatch", "Status: " + to_string(response.status));

                    if(response.ok)
                        this->onmessage(response.content);
                    else
                        this->onerror(response.error);
                });

            } else {
                log_A(TAG::WSS, this->endpoint + "::ThreadMain", "KeepAlive");
            }

            // Effettua poll a livello più lento e ignora operazioni read/write
            this->channel->poll(this->is_computing ? SOCKET_ACTIVE_POLL : SOCKET_INACTIVE_POLL);
        }

        // Il canale è stato terminato in modo inaspettato e non richiesto dall'utente
        if(this->is_computing){
            this->onerror("Bad connection");
        }

        if(this->channel) {
            delete this->channel;
                   this->channel = 0;
        }

        this->stopping = false;
        this->running = false;

        log_A(TAG::WSS, this->endpoint + "::ThreadMain", "[r] complete");

        if(this->onclose) 
            this->onclose(this->key);
        
        this->cv.notify_one();

    }

    void Socket::pause() {
        log_A(TAG::WSS, this->endpoint + "::Pause", "");
        this->is_computing = false;
    }

    void Socket::resume() {
        log_A(TAG::WSS, this->endpoint + "::Resume", "");
        this->is_computing = true;
    }

    void Socket::reset() {
        this->buffer.content  = "";
        this->buffer.is_send = false;
    }

    void Socket::setBuffer(const BaseRequest& request){
        this->reset();
        this->buffer.content = request.serialize();

        log_A(TAG::WSS, this->endpoint + "::Buffer", this->buffer.content);
    }

    // handle blocking deletion or subscriber/unsubscriber wrapper mutex
    void Socket::asyncDelete(std::string key, void(*onclose)(const std::string k)) {

        if(this->running && !this->stopping) {

            this->onclose = onclose;
            this->key = key;
            this->stopping = true;

            this->pause(); 

            // may not exist as well (if errors creating)
            if(this->channel)
                this->channel->close();

        }

    }

    void Socket::syncDelete() {

        this->asyncDelete(UUID::generate(), [](const string k){
            log_A(TAG::INF, "Destroy handler", k);
        });

        if(this->running) {
            if(this->stopping) {
                std::unique_lock<std::mutex> lck(this->mtx);
                this->cv.wait(lck, [this](){ return !this->stopping; });
            }
        }

    }

    Socket::~Socket(){

        assert(!this->running);
        log_A(TAG::WSS, this->endpoint + "::Destroy", "");

    }

    Socket::Socket( const std::string& node, 
                    void (*onmessage)(const std::string message), 
                    void (*onerror)(const std::string error)) {

        this->endpoint = node;

        log_A(TAG::WSS, this->endpoint + "::Create", "");

        this->onmessage = onmessage;
        this->onerror = onerror;
        this->onclose = 0;

        this->reset();
        this->is_computing = true;

        this->watcher = std::thread(&Socket::ThreadMain, this);
        this->watcher.detach();
        
    }

}
