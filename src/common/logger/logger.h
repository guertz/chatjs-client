#ifndef COMMON_LOGGER_LOGGER_H
#define COMMON_LOGGER_LOGGER_H

#include "env.h"

enum TAG{
  CSL  = 0,
  WS   = 1,
  INFO = 2
};


// Con il metodo macro per notificare i cambiamenti della maschera a tutti i file
// Bisogna ricompilare tutto. Oppure bisogna utilizzare il sistema a funzione log
// che fa gli if sul momento
// Wrap with { } mustaches
// Wrap with ( )

#define LOGGER(TYPE, LEV, ATTR, LOG)            \
    print_log(                                  \
        static_cast<const TAG>(TYPE),           \
        static_cast<const unsigned int>(LEV),   \
        ATTR,                                   \
        LOG                                     \
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

// questo interno c++ per azioni javascript
// per webview console.log posso usare quello webview integrato senza mia funzione
#define log_csl(attr, log_msg)       { if(1 & DEBUG_MASK) { LOGGER(TAG::CSL, 0, attr, log_msg); } }
#define  log_ws(attr, log_msg)       { if(1 & DEBUG_MASK) { LOGGER(TAG::WS,  0, attr, log_msg); } }

// log_err (stderr)

#define log_base_void(log_msg)       { if(1 & DEBUG_MASK) { LOGGER(TAG::INFO, 1,   "", log_msg); } }
#define log_base(attr, log_msg)      { if(1 & DEBUG_MASK) { LOGGER(TAG::INFO, 1, attr, log_msg); } }

#define log_details_void(log_msg)    { if(2 & DEBUG_MASK) { LOGGER(TAG::INFO, 2,   "", log_msg); } }
#define log_details(attr, log_msg)   { if(2 & DEBUG_MASK) { LOGGER(TAG::INFO, 2, attr, log_msg); } }

                                    // MASK = 4 però 3° tipo di log
#define log_pedantic_void(log_msg)   { if(4 & DEBUG_MASK) { LOGGER(TAG::INFO, 3,   "", log_msg); } }
#define log_pedantic(attr, log_msg)  { if(4 & DEBUG_MASK) { LOGGER(TAG::INFO, 3, attr, log_msg); } }


void print_log(const TAG tag, const unsigned int level, const std::string& attr, const std::string& log_msg);

#endif