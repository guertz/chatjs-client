#include "env.h"

#ifndef LOGGER_LOGGER_H
#define LOGGER_LOGGER_H

// Con il metodo macro per notificare i cambiamenti della maschera a tutti i file
// Bisogna ricompilare tutto. Oppure bisogna utilizzare il sistema a funzione log
// che fa gli if sul momento

#ifndef DEBUG_MODE
    #define DEBUG_MASK 0
#endif

// Default value
#ifndef DEBUG_MASK
    #define DEBUG_MASK 1
#endif

// Wrap with { } mustaches
// Wrap with ( )

#define LOGGER(TYPE, LEV, ATTR, LOG)            \
    print_log(                                  \
        static_cast<const TAG>(TYPE),           \
        static_cast<const unsigned int>(LEV),   \
        reinterpret_cast<const char*>(ATTR),    \
        reinterpret_cast<const char*>(LOG)      \
    );

// file .h o .cc
// A che scopo?
// log custom?
// sistema ottale per scegliere error in modo condizionale
//  extra
// LOG_ALL

// log_constole è come log_base ma filtrato
// pedantic                  MASK= 4
// details                   MASK= 2
// base                      MASK= 1 

// 4        + 2       + 1    ALL = 7 
// pedantic + details + base 

// 2       + 1               MID = 3
// details + base            

// 1                         LOW = 1
// base

#define log_csl(attr, log_msg)       { if(1 & DEBUG_MASK) { LOGGER(TAG::CSL, 0, attr, log_msg); } }

#define log_base_void(log_msg)       { if(1 & DEBUG_MASK) { LOGGER(TAG::INFO, 1,   "", log_msg); } }
#define log_base(attr, log_msg)      { if(1 & DEBUG_MASK) { LOGGER(TAG::INFO, 1, attr, log_msg); } }

#define log_details_void(log_msg)    { if(2 & DEBUG_MASK) { LOGGER(TAG::INFO, 2,   "", log_msg); } }
#define log_details(attr, log_msg)   { if(2 & DEBUG_MASK) { LOGGER(TAG::INFO, 2, attr, log_msg); } }

                                      // MASK = 4 però 3° tipo di log
#define log_pedantic_void(log_msg)   { if(4 & DEBUG_MASK) { LOGGER(TAG::INFO, 3,   "", log_msg); } }
#define log_pedantic(attr, log_msg)  { if(4 & DEBUG_MASK) { LOGGER(TAG::INFO, 3, attr, log_msg); } }

enum TAG{
  CSL = 0,
  INFO = 1
};

void print_log(const TAG tag, const unsigned int level, const char* attr, const char* log_msg);

#endif