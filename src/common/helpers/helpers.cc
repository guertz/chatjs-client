#include<iostream>
#include <cstring>
#include <cstdarg>
#include "helpers.h"

using namespace std;

namespace Helpers {
    namespace safeptr {

        void free_block(const char*& kPtrChar){
            if(kPtrChar){
                delete[] kPtrChar;
                kPtrChar = 0;
            }
        }

        void free_block(char*& ptrChar){
            if(ptrChar){
                delete[] ptrChar;
                ptrChar = 0;
            }
        }

        void *serialize(char *voidPtrChar){
            return reinterpret_cast<void*>(voidPtrChar);
        }

        char *deserialize(void *charPtrVoid){
            return reinterpret_cast<char*>(charPtrVoid);
        }

        const char* parse_asset(const char* asset){
            return reinterpret_cast<const char* const>(asset);
        }

    }

    namespace safestr {
        
        char *bufferizable(const unsigned int size){
            char *buf = new char[size];
            strncpy(buf, "",size);

            return buf;
        }
        
        char *duplicate(const char * const kPtrChar){

            char *buf = new char[strlen(kPtrChar) + 1];
            strcpy(buf,kPtrChar);

            return buf;
        }

    }

    namespace js {

        // TODO:
        //      Optimize with c++ native library for string buffers
        //      Riportare strlen tutte le volte e il numero di parti è inutile
        // this duplicates
        char *compact(const unsigned size, const unsigned int parts, const char *part...){

            char *buffer = safestr::bufferizable(size);

            va_list args;
            va_start(args, part);

            for(unsigned int i=0; i<parts; i++){
                strcat(buffer, part); // strncat ?
                part = va_arg(args, const char*);
            }
            
            va_end(args);

            return buffer;
        }

        void* prepare(const char * const kPtrChar) {
            return safeptr::serialize(safestr::duplicate(kPtrChar));
        }
        
    }
}