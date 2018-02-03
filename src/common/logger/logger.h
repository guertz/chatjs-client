#ifndef COMMON_LOGGER_LOGGER_H
#define COMMON_LOGGER_LOGGER_H

#include "env.h"
/**
 *  @brief Sistema di logging.
 *  Descrizione del funzionamento e configurazioni:
 *  + I log sono di default abilitati da (DEBUG_MASK > 0) ::env.h per dettagli
 *  + I livelli di log configurabili sono:
 *      - log_csl  sempre attivo da DEBUG_MASK
 *      - log_ws   sempre attivo da DEBUG_MASK
 *      - log_warn sempre attivo da DEBUG_MASK
 *      - log_err  sempre attivo da DEBUG_MASK
 *      - log_base configurabile a più livelli: 
 *          - base     (MASK = 1)
 *          - details  (MASK = 2)
 *          - pedantic (MASK = 4)
 *        è possibile creare una combinazione tra i livelli come:
 *          - base + details            (MASK = 3)
 *          - base + details + pedantic (MASK = 7)
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
#define log_csl(attr, log_msg)       { if(DEBUG_MASK) { LOGGER(TAG::CSL, 0, attr, log_msg); } }
#define log_ws(attr, log_msg)        { if(DEBUG_MASK) { LOGGER(TAG::WS,  0, attr, log_msg); } }

#define log_warn(attr, log_msg)      { if(DEBUG_MASK) { LOGGER(TAG::WARN,  0, attr, log_msg); } }
#define log_err(attr, log_msg)       { if(DEBUG_MASK) { LOGGER(TAG::ERR,   0, attr, log_msg); } }

// Può essere customizzato per creare n livelli
#define log_base(attr, log_msg)      { if(1 & DEBUG_MASK) { LOGGER(TAG::INFO, 1, attr, log_msg); } }
#define log_details(attr, log_msg)   { if(2 & DEBUG_MASK) { LOGGER(TAG::INFO, 2, attr, log_msg); } }
#define log_pedantic(attr, log_msg)  { if(4 & DEBUG_MASK) { LOGGER(TAG::INFO, 3, attr, log_msg); } }


void print_log(const TAG tag, const unsigned int level, const std::string& attr, const std::string& log_msg);

#endif