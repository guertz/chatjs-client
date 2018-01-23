#ifndef WS_CUSTOM_H
#define WS_CUSTOM_H

#include "easywsclient.h"

#include "definitions/request.h"
#include "definitions/response.h"
#include "exceptions/exceptions.h"

#include "env.h"

#include <iostream>
#include <thread>
#include <stack>

using namespace std;
using easywsclient::WebSocket;

namespace ws{

    typedef struct socket_args {
        bool is_send;
        string buffer;
    } SocketArgs;

    // NEXT: Reconnect
    // NEXT: prevent null pointer on websocket
    class Socket {

        private:

            SocketArgs arguments;
            bool is_computing;
            WebSocket::pointer channel;
            thread watcher; 

            void (*onmessage)(const string message); 
            void (*onerror)(const string error);

            // _ private convention
            void reset();
            void ThreadMain();

        public:
            // will compute
            Socket(const string& s, void (*onmessage)(const string message), void(*onerror)(const string error));
            ~Socket();

            void resume();
            void pause();

            void setBuffer(const RequestDefinition::Request& request);
    };
}

#endif