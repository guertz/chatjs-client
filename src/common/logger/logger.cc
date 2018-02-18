#include <iostream>
#include <algorithm>
#include <string>
#include "logger.h"

using namespace std;
/**
 * @brief Definizione sistema di logging
 * @file logger.cc
 */

// TODO: Limit length
// TODO: limit colors
// TODO: print level as a string

/** Metodo interno per la stampa dei log */
void print_log(const LEV lev, const TAG tag, std::string attr, std::string log_msg) {

    string composed_message = "";

        log_msg.erase(std::remove(log_msg.begin(), log_msg.end(), '\n'), log_msg.end());

    switch(tag) {
        case TAG::INF:
            composed_message = "[ INF" + to_string(lev) + "@" + attr + " ]: " + log_msg + "\n";
            break;

        case TAG::CSL:
            composed_message = "[ CSL" + to_string(lev) + "@" + attr + " ]: " + log_msg + "\n";
            break;

        case TAG::WSS:
            composed_message = "[ WSS" + to_string(lev) + "@" + attr + " ]: " + log_msg + "\n";
            break;

        case TAG::OBJ:
            composed_message = "[ OBJ" + to_string(lev) + "@" + attr + " ]: " + log_msg + "\n";
            break;

        case TAG::CMP:
            composed_message = "[ CMP" + to_string(lev) + "@" + attr + " ]: " + log_msg + "\n";
            break;

        case TAG::STA:
            composed_message = "[ STA" + to_string(lev) + "@ " + attr + " ]: " + log_msg + "\n";
            break;

        default:
            break;

    }

    // Single atomic operation
    cout<<composed_message;
        
}