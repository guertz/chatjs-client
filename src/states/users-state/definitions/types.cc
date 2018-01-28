#include "types.h"

using namespace std;

namespace States {
    namespace UsersState{

        STREAMSIGNAL str_to_enum(const string& STREAM_ACTION){
            if(STREAM_ACTION.compare("open") == 0)
                return STREAMSIGNAL::OPEN;

            return STREAMSIGNAL::CLOSE;
        }

        string enum_to_str(const STREAMSIGNAL STREAM_ACTION){

            switch(STREAM_ACTION) {
                case STREAMSIGNAL::OPEN: 
                    return "open";
                default:
                    return "close";
            }
        }

    }
}