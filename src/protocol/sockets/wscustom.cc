
#include <iostream>
#include <thread>
#include <thread>

#include "wscustom.h"

#include "common/helpers/helpers.h"
#include "common/logger/logger.h"

using json = nlohmann::json;
using WebSocket = easywsclient::WebSocket;
using namespace Helpers;

namespace ws {
 
    void Socket::ThreadMain(){

        this->channel = WebSocket::from_url(this->path);
        this->is_computing = true;

        // Handle (connection errors):
        //      - node not exists
        //      - connection errors
        assert(this->channel);
        while(this->channel && this->channel->getReadyState() != WebSocket::CLOSED) {

            if(this->is_computing) {

                if(this->arguments.buffer.size() > 0 && !this->arguments.is_send) { 
                    this->channel->send(this->arguments.buffer);
                    this->arguments.is_send = true;
                } else
                    this->reset();
                

                this->channel->dispatch([this](const string& json_response) {
                    
                    BaseResponse response(json::parse(json_response));

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
    // Lock channel as well
    // Boost & async event driven (Asio)
    void Socket::reset() {
        this->arguments.buffer  = "";
        this->arguments.is_send = false;
    }

    void Socket::setBuffer(BaseRequest& request){

        this->reset();

        json serialized_request = request.to_json();

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

        this->path = "ws://" + SERVER_HOST + ":" + SERVER_PORT + "/" +s;

        this->onmessage = onmessage;
        this->onerror = onerror;

        this->reset();
        this->is_computing = true; // || false?

        // handle thread channel not open exception
        try {
            this->watcher = std::thread(&Socket::ThreadMain, this);
            this->watcher.detach();
        } catch(const ws::SocketTermination& termination_exception ){
            throw termination_exception;
        }
        
    }
}
