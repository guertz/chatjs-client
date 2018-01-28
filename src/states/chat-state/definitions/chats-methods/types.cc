#include "types.h"

using namespace std;

namespace States {

    namespace ChatState {

        namespace ChatsMethods {
            
            TYPE str_to_enum(const string& ACTION){
                if(ACTION.compare("connect") == 0)
                    return TYPE::CONNECT;

                if(ACTION.compare("create") == 0)
                    return TYPE::CREATE;

                return TYPE::ALL;
            }

            string enum_to_str(const TYPE ACTION){

                switch(ACTION) {
                    case TYPE::CONNECT: 
                        return "connect";

                    case TYPE::CREATE:
                        return "create";

                    default:
                        return "";
                }
            }

        }
        
    }
}