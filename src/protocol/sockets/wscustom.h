#ifndef WS_CUSTOM_H
#define WS_CUSTOM_H

#include "easywsclient.h"
#include "exceptions/exceptions.h"

#include <iostream>
#include <thread>
#include <stack>

using namespace std;
using easywsclient::WebSocket;

namespace ws{

    class Socket {
        private:
            bool is_stream;
            bool is_send;
            bool is_computing;

            string buffer;

            WebSocket::pointer channel;
            thread watcher; 

            void (*onmessage)(const char* ); 

            void clearParams();
            void ThreadMain();

        public:
            Socket(const string& s, void (*)(const char* ));
            ~Socket();

            void resume();
            void pause();
            void stop();

            void setBuffer(const string &s, bool stream);
            void compute();
    };
}

#endif