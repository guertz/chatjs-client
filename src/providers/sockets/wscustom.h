#ifndef websocket_custom_header
#define websocket_custom_header

#include "easywsclient.h"

#include <iostream>
#include <string.h>
#include <cstdlib>
#include <thread>
#include <unistd.h>
#include <exception>

using namespace std;
using easywsclient::WebSocket;

// create my namespace
namespace ws{

    // base class to extend
    class SocketException: public exception
    {
      virtual const int code() const throw()
      {
        return 100;
      }
      virtual const char* what() const throw()
      {
        return "Il canale di comunicazione è configurato in modo scorretto per lo scopo che si vuole ottenere. Errore in lettura se il thread è a canale singolo continuo. Errore in scrittura se il thread è a canale singolo eseguito una sola volta";
      }
    };

    // base class to extend
    class SocketComputingException: public exception
    {
        virtual const int code() const throw()
        {
            return 101;
        }
        virtual const char* what() const throw()
        {
            return "Impossibile eseguire questa operazione con il canale occupato";
        }
    };

    /*
    namespace OPERATIONS {
        enum STATUS {
            READ,
            READING,
            WRITE,
            WRITING
        };
    }
    
    namespace ACTIONS {
        enum CRUD {
            CREATE,
            UPDATE,
            READ,
            DELETE
        };
    }
    */

    struct thread_data {
        WebSocket::pointer channel;
        string buffer;
        bool SINGLE;
        bool free;
        void (*callback)(const char* arg);
    };

    class Socket {
        private:
            thread* watcher; 
            // OPTIMIZATION: single thread wrapper that permorm poll evey cicles (queue)

            bool COMPUTING;
            struct thread_data tdat;

            void initZ(string s, bool t);

        public:
            Socket(string s);
            Socket(string s, bool t);

            void get();
            void write(const string &s);
            
            void get(void (*fn)(const char* arg));
            void write(const string &s, void (*fn)(const char* arg));
            
            void stop();

            void set_type(bool t);
    };
}

#endif