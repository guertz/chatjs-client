#include "types.h"

using namespace std;

namespace States {

    namespace ChatState {


        namespace ChatMethods {
            
            TYPE str_to_enum(const string& ACTION){
                if(ACTION.compare("join") == 0)
                    return TYPE::JOIN;

                if(ACTION.compare("send") == 0)
                    return TYPE::SEND;

                return TYPE::ALL;
            }

            string enum_to_str(const TYPE ACTION){

                switch(ACTION) {
                    case TYPE::JOIN: 
                        return "join";

                    case TYPE::SEND:
                        return "send";

                    default:
                        return "";
                }
            }

        }
    }
}