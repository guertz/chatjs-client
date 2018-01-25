#ifndef PROTOCOL_SOCKETS_WSCUSTOM_H
#define PROTOCOL_SOCKETS_WSCUSTOM_H

#include <thread>

#include "easywsclient.h"

#include "definitions/request.h"
#include "definitions/response.h"
#include "exceptions/exceptions.h"

#include "env.h"

namespace ws{

    typedef struct socket_args {
        bool is_send;
        std::string buffer;
    } SocketArgs;

    // NEXT: Reconnect
    // NEXT: prevent null pointer on websocket
    // Next: on channel error, cal onerror method with exception
    class Socket {

        private:

            SocketArgs arguments;
            bool is_computing;
            easywsclient::WebSocket::pointer channel;
            thread watcher; 

            void (*onmessage)(const std::string message); 
            void (*onerror)(const std::string error);

            // _ private convention
            void reset();
            void ThreadMain();

        public:
            // will compute
            Socket(const std::string& s, void (*onmessage)(const std::string message), void(*onerror)(const std::string error));
            ~Socket();

            void resume();
            void pause();

            void setBuffer(BaseRequest& request);
    };
}

#endif