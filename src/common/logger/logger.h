#ifndef COMMON_LOGGER_LOGGER_H
#define COMMON_LOGGER_LOGGER_H

/**
 *  @brief Interfaccia sistema di logging.
 *  @file logger.h
 */

#define LOG_LEN 60
#define WIN_CONSOLE

/** Abilitazione dello stream di uscita su cerr (per log errori) oltre che cout */
// #define LOG_CERR

/** Abilitazione debug webview per stampare log provenienti da essa (console + dispatch/execute) */
// #define WEBVIEW_DEBUG // TODO: won't cut logs and will use its own system NSLog

/** Livello di log */
#define DEBUG_MASK 0

/** Tipo oggetti da loggare */
#define DEBUG_TASK 0

#ifdef DEBUG_MODE
    
    #undef DEBUG_MASK
    #undef DEBUG_TASK

    // refresh-app richiesto se modificati i valori
    #define DEBUG_MASK 3  // Log all levels but not pedantic
    #define DEBUG_TASK 55 // Log all type except OBJ (Objects)

#endif

/** Tags per identificare il tipo di azione di log */
enum TAG {
  INF = 1,  /**< Base, log per tracciare informazioni */
  CSL = 2,  /**< Console, log relativo alla webview */
  WSS = 4,  /**< Websockets, log relativo ai websocket */
  OBJ = 8,  /**< Object, per log relativo a data models */
  CMP = 16, /**< Components, per log relativo a componenti */
  STA = 32  /**< States, per log relativo a data states */
};

enum LEV {
    LOGN = 0, /**< Standard output log (livello N)*/
    LOGA = 1, /**< Standard output log (livello A)*/
    LOGB = 2, /**< Standard output log (livello B)*/
    LOGC = 4  /**< Standard output log (livello C)*/
};

#define LOGGER(lev, tag, attr, msg)        \
    print_log(                             \
        static_cast<const LEV>(lev),       \
        static_cast<const TAG>(tag),       \
        attr,                              \
        msg                                \
    );

#define log_A(tag, attr, msg)       { if( (tag & DEBUG_TASK) && (LEV::LOGA & DEBUG_MASK) ) { LOGGER(LEV::LOGA, tag, attr, msg); } }
#define log_B(tag, attr, msg)       { if( (tag & DEBUG_TASK) && (LEV::LOGB & DEBUG_MASK) ) { LOGGER(LEV::LOGB, tag, attr, msg); } }
#define log_C(tag, attr, msg)       { if( (tag & DEBUG_TASK) && (LEV::LOGC & DEBUG_MASK) ) { LOGGER(LEV::LOGC, tag, attr, msg); } }
#define log_n(lev, tag, attr, msg)  { if( (tag & DEBUG_TASK) && (lev & DEBUG_MASK) )       { LOGGER(LEV::LOGN, tag, attr, msg); } }

void print_log(const LEV lev, const TAG tag, std::string attr, std::string log_msg);

#endif