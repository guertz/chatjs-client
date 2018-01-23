#ifndef WS_CUSTOM_EXCEPTIONS_H
#define WS_CUSTOM_EXCEPTIONS_H

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