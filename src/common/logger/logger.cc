#include <iostream>
#include <algorithm>
#include <string>
#include "logger.h"

using namespace std;
/**
 * @brief Definizione sistema di logging
 * @file logger.cc
 */

/** Metodo interno per la stampa dei log */
void print_log(const TAG tag, const unsigned int level, std::string attr, std::string log_msg) {

    string composed_message = "";

           log_msg.erase(std::remove(log_msg.begin(), log_msg.end(), '\n'), log_msg.end());

    // limit all lenght like web_ui.cc
    // color output cross-platform?
    switch(tag) {
        
        case TAG::CSL:
            composed_message = "[ CSL   @ " + attr + "]: " + log_msg + ".\n";
            break;

        case TAG::WS:
            composed_message = "[ WS    @ " + attr + "]: " + log_msg + ".\n";
            break;

        case TAG::WARN:
            composed_message = "[ WARN  @ " + attr + "]: " + log_msg + ".\n";
            break;

        case TAG::ERR:
            composed_message = "[ ERR   @ " + attr + "]: " + log_msg + ".\n";

            #ifdef LOG_CERR
                cerr<<composed_message;
            #endif

            break;

        case TAG::INFO:
            composed_message = "[ INFO" + to_string(level) + " @ " + attr + "]: " + log_msg + ".\n";
            break;

        default:
            break;

    }


    cout<<composed_message;
    
}