#ifndef PROTOCOL_SOCKETS_EXCEPTIONS_EXCEPTIONS_H
#define PROTOCOL_SOCKETS_EXCEPTIONS_EXCEPTIONS_H

#include <exception>

using namespace std;
namespace ws {

    class SocketTermination: public exception {
        virtual const char* what() const throw() {
            return "Canale di comunicazione interrotto.";
        }
    };
    
}

#endif