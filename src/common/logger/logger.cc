#include <iostream>
#include "logger.h"

using namespace std;

void print_log(const TAG tag, const unsigned int level, const string& attr, const string& log_msg) {

    switch(tag) {
        // change color
        case TAG::CSL:
            cout<<" [ JS @ "<<attr<<"]: "<<log_msg<<endl;
            break;

        default:
            cout<<" [ INFO"<<level<<" @ "<<attr<<"]: "<<log_msg<<endl;
            break;
    
    }
}