#include <iostream>
#include "logger.h"

using namespace std;

void print_log(const TAG tag, const unsigned int level, const string& attr, const string& log_msg) {

    string composed_message = "";
    switch(tag) {
        // change color
        case TAG::CSL:
            composed_message = "[ JS @ " + attr +"]: " + log_msg + ".\n";
            break;

        case TAG::WS:
            composed_message = "[ WS @ " + attr +"]: " + log_msg + ".\n";
            break;

        default:
            composed_message = "[ INFO" + to_string(level) +" @ " +attr+"]: "+log_msg + ".\n";
            break;
    
    }

    cout<<composed_message;
}