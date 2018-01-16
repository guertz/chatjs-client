#include <vector>

using namespace std;

#ifndef user_definition_h
#define user_definition_h

namespace UserDefinition {
    
        struct User{
            string name;
            string image;
        };

        struct ChatBox : User {
            string lastmessage;
        };

}
#endif