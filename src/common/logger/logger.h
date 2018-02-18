#ifndef COMMON_LOGGER_LOGGER_H
#define COMMON_LOGGER_LOGGER_H

/**
 *  @brief Interfaccia sistema di logging.
 *  @file logger.h
 */

/** Definizione lunghezza stringa log, utilizzato in web-ui.cc */
#define LOG_LEN 60

/** Abilitazione console di log su windows (vedi main.cc) */
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
    #define DEBUG_TASK 53 // Log all type except OBJ, CSL

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

/** Tags per identificare il livello di log */
enum LEV {
    LOGN = 0, /**< Standard output log (livello N)*/
    LOG1 = 1, /**< Standard output log (livello base)*/
    LOG2 = 2, /**< Standard output log (livello details)*/
    LOG3 = 4  /**< Standard output log (livello pedantic)*/
};

#define LOGGER(lev, tag, attr, msg)        \
    print_log(                             \
        static_cast<const LEV>(lev),       \
        static_cast<const TAG>(tag),       \
        attr,                              \
        msg                                \
    );

/** Macro per livello di log base */
#define log_base(tag, attr, msg)     { if( (tag & DEBUG_TASK) && (LEV::LOG1 & DEBUG_MASK) ) { LOGGER(LEV::LOG1, tag, attr, msg); } }

/** Macro per livello di log details */
#define log_details(tag, attr, msg)  { if( (tag & DEBUG_TASK) && (LEV::LOG2 & DEBUG_MASK) ) { LOGGER(LEV::LOG2, tag, attr, msg); } }

/** Macro per livello di log pedantic */
#define log_pedantic(tag, attr, msg) { if( (tag & DEBUG_TASK) && (LEV::LOG3 & DEBUG_MASK) ) { LOGGER(LEV::LOG3, tag, attr, msg); } }

/** Macro per livello di log custom */
#define log_n(lev, tag, attr, msg)   { if( (tag & DEBUG_TASK) && (lev & DEBUG_MASK) )       { LOGGER(LEV::LOGN, tag, attr, msg); } }

/**
 * Metodo per stampare un messaggio di log
 *
 * @param[in] lev Fare riferimento a ::LEV
 * @param[in] tag Fare riferimento a ::TAG
 * @param[in] attr Riferimento al messaggio di log (componente/metodo)
 * @param[in] log_msg Messaggio di log   
 */
void print_log(const LEV lev, const TAG tag, std::string attr, std::string log_msg);

#endif