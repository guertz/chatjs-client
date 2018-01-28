#ifndef STATES_CHAT_STATE_DEFINITIONS_CHATSMETHODS_TYPES_H
#define STATES_CHAT_STATE_DEFINITIONS_CHATSMETHODS_TYPES_H

#include <iostream>

namespace States {

    namespace ChatState {

        namespace ChatsMethods {
            
            enum TYPE {
                ALL     = 0,
                CONNECT = 1,
                CREATE  = 2
            };

            TYPE str_to_enum(const std::string& ACTION);
            std::string enum_to_str(const TYPE  ACTION);
        }
    }

}

#endif