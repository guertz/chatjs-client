#include "wscustom.h"

#include "common/helpers/helpers.h"
#include "common/logger/logger.h"

#include <iostream>
#include <cstdlib>
#include <thread>
#include <unistd.h>
#include <signal.h>

using namespace Helpers;

namespace ws {
 
    void Socket::ThreadMain(){

        this->is_computing = true;

        while(this->channel->getReadyState() != WebSocket::CLOSED) {

            if(this->is_computing) {

                if(this->arguments.buffer.size() > 0 && !this->arguments.is_send) { 
                    this->channel->send(this->arguments.buffer);
                    this->arguments.is_send = true;
                } else
                    this->reset();
                

                this->channel->dispatch([this](const string& json_response) {
                    
                    ResponseDefinition::Response response = json::parse(json_response);

                    if(response.ok)
                        this->onmessage(response.content);
                    else
                        this->onerror(response.error);
                });

            }

            this->channel->poll(this->is_computing ? SOCKET_ACTIVE_POLL : SOCKET_INACTIVE_POLL);

        }

        // Il canale è stato terminato in modo inaspettato e non richiesto dall'utente
        if(this->is_computing){
            SocketTermination exception;
            throw exception;
        }

    }

    void Socket::pause() {
        this->is_computing = false;
    }

    void Socket::resume() {
        this->is_computing = true;
    }

    // Mutex arguments
    // Mutex computing
    void Socket::reset() {
        this->arguments.buffer  = "";
        this->arguments.is_send = false;
    }

    void Socket::setBuffer(const RequestDefinition::Request& request){

        this->reset();

        json serialized_request = request;

        this->arguments.buffer = serialized_request.dump();
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

    Socket::Socket( const string& s, 
                    void (*onmessage)(const string message), 
                    void(*onerror)(const string error)) {
        
        this->channel = WebSocket::from_url("ws://" + SERVER_HOST + ":" + SERVER_PORT + "/" +s);

        this->onmessage = onmessage;
        this->onerror = onerror;

        this->reset();
        this->is_computing = true;

        // handle thread channel not open exception
        try {
            this->watcher = std::thread(&Socket::ThreadMain, this);
            this->watcher.detach();
        } catch(const ws::SocketTermination& termination_exception ){
            throw termination_exception;
        }
        
    }
}
