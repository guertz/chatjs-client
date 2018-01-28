#ifndef STATES_CHAT_STATE_DEFINITIONS_CHATMETHODS_TYPES_H
#define STATES_CHAT_STATE_DEFINITIONS_CHATMETHODS_TYPES_H

#include <iostream>

namespace States {

    namespace ChatState {


        namespace ChatMethods {
            
            enum TYPE {
                ALL     = 0,
                JOIN    = 1,
                SEND    = 2
            };

            TYPE str_to_enum(const std::string& ACTION);
            std::string enum_to_str(const TYPE  ACTION);
        }
        
    }
}

#endif