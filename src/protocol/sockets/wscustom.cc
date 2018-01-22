#include "easywsclient.h"
#include "wscustom.h"
#include "env.h"

#include "definitions/request.h"
#include "definitions/response.h"

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

        //      => server chiude solo su errori
        //         sempre il client a decidere
        //         e iniziare le comunicazioni
        //         NEXT: Schedule multiple requests
        //         set is_stream in constructor?
        //         activate compute only when needed or set default state to pause
        //         Types: (2 classes)
        //              - flow
        //              - request & response
        assert(this->channel);
        while(this->channel->getReadyState() != WebSocket::CLOSED) {

            log_base("Socket", "Looping");

            if(this->is_computing) {
                log_base("Socket", "Computing");

                if(this->buffer.size() > 0 && !this->is_send) { 
                    this->channel->send(this->buffer);
                    this->is_send = true;
                }
                // I probably do not need an else
                // } else {

                    this->channel->dispatch([this](const string& socketResponse) {
                        
                        log_base("received", socketResponse.c_str());

                        json json_response = json::parse(socketResponse);
                        ws::ResponseDefinition::Response response = json_response;

                        this->clearParams();

                        if(!this->is_stream)
                            this->pause();

                        this->onmessage(safestr::duplicate(json_response.at("content").dump().c_str()));
                    });

                // }
            }

            this->channel->poll(this->is_computing ? SOCKET_ACTIVE_POLL : SOCKET_INACTIVE_POLL);

        }

        if(this->channel->getReadyState() == WebSocket::CLOSED ) {
            
            if(this->channel) {
                delete this->channel;
                    this->channel = 0;
            }

            if(this->is_computing){
                SocketTermination exception;
                throw exception;
            }
        }

    }

    void Socket::pause() {
        this->is_computing = false;
    }

    void Socket::resume() {
        this->is_computing = true;
    }

    // Group attrivutes
    // Mutex on buffer (and its attribute)
    // will loose data?
    void Socket::clearParams() {
        this->buffer = "";
        this->is_send = false;
        this->is_stream = false;
        this->is_computing = false;
    }

    // prevent stop on already stopped?
    void Socket::stop() {
        this->clearParams();
        this->channel->close();
        if(this->watcher.joinable()) this->watcher.join();
    }

    // prevent compute or setbuffer after stop
    void Socket::compute() {

        if(this->is_computing) {
            ws::SocketComputing computing_exception;
            throw computing_exception;
        } else {
            try {
                this->watcher = std::thread(&Socket::ThreadMain, this);
                this->watcher.detach();
            } catch(const ws::SocketTermination& termination_exception ){
                throw termination_exception;
            }
        }
    }

    // Compose request, use templates
    // TODO: request format on server
    // TODO: throw close if no channel
    // TODO: Connection error => got closed channel?
    // TODO: reconnection
    void Socket::setBuffer(const string &s, bool stream){

        this->clearParams();
        this->is_stream = stream;
        this->resume();

        RequestDefinition::Request auth_request = RequestDefinition::createEmpty();
            auth_request.content = s;

        // JSON_stringify
        json json_auth_request = auth_request;

        this->buffer = json_auth_request.dump();
    }

    Socket::~Socket(){
        log_base("Socket", "destroy");
        this->stop();
    }

    Socket::Socket(const string& s, void (*handler)(const char* )) {
        
        log_base("Socket", "create");
        this->channel = WebSocket::from_url("ws://localhost:8000/" +s);

        this->onmessage = handler;
        this->clearParams();

        // if not channel
        //  throw error
    }
}
