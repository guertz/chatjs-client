#ifndef COMMON_LOGGER_LOGGER_H
#define COMMON_LOGGER_LOGGER_H

#include "env.h"
/**
 *  @brief Interfaccia sistema di logging.
 *  @file logger.h
 *  Descrizione del funzionamento e configurazioni:
 *  + I log sono di default abilitati da (DEBUG_MASK > 0) env.h per dettagli
 *  + I livelli di log configurabili sono riportati in questo file.
 *      Nel caso di ::log_base, ::log_details, ::log_pedantic è possibile 
 *      combinare i livelli di debug mask per abilitare più logger contemporaneamente.
 */

/** Tags per identificare il tipo di azione di log */
enum TAG{
  CSL  = 0 /**< Console, log relativo alla webview */,
  WS   = 1 /**< Websockets, log relativo ai websocket */,
  INFO = 2 /**< Info, log per tracciare informazioni */,
  WARN = 3 /**< Warning, log per tracciare possibili errori */,
  ERR  = 4 /**< Error, log per tracciare errori */
};


// logger.cc => metodo esterno, non bisogna ricompilare tutto
// Wrap with { }/( ) [per evitare dispersione o mal interpretazione del contenuto]

#define LOGGER(TYPE, LEV, ATTR, LOG)            \
    print_log(                                  \
        static_cast<const TAG>(TYPE),           \
        static_cast<const unsigned int>(LEV),   \
        ATTR,                                   \
        LOG                                     \
    );

// per metodi .cc, webview ha il suo sitema interno che dovrà essere rimpiazzato (zerge, logging system)
/** ::log_csl      sempre attivo da DEBUG_MASK */
#define log_csl(attr, log_msg)       { if(DEBUG_MASK) { LOGGER(TAG::CSL, 0, attr, log_msg); } }
/** ::log_ws       sempre attivo da DEBUG_MASK */
#define log_ws(attr, log_msg)        { if(DEBUG_MASK) { LOGGER(TAG::WS,  0, attr, log_msg); } }

/** ::log_warn     sempre attivo da DEBUG_MASK */
#define log_warn(attr, log_msg)      { if(DEBUG_MASK) { LOGGER(TAG::WARN,  0, attr, log_msg); } }
/** ::log_err      sempre attivo da DEBUG_MASK */
#define log_err(attr, log_msg)       { if(DEBUG_MASK) { LOGGER(TAG::ERR,   0, attr, log_msg); } }

// Può essere customizzato per creare n livelli
/** ::log_base     attivo con MASK = 1 */
#define log_base(attr, log_msg)      { if(1 & DEBUG_MASK) { LOGGER(TAG::INFO, 1, attr, log_msg); } }
/** ::log_details  attivo con MASK = 2 */
#define log_details(attr, log_msg)   { if(2 & DEBUG_MASK) { LOGGER(TAG::INFO, 2, attr, log_msg); } }
/** ::log_pedantic attivo con MASK = 4 */
#define log_pedantic(attr, log_msg)  { if(4 & DEBUG_MASK) { LOGGER(TAG::INFO, 3, attr, log_msg); } }

void print_log(const TAG tag, const unsigned int level, std::string attr, std::string log_msg);

#endif