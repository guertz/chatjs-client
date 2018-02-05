#ifndef ENV
#define ENV

/**
 * @brief  Variabili d'ambiente condivise.
 */

/** Variabile per limitare il numero di messaggi per chat */
// const unsigned int MESSAGES   = 10;

/** Tempo espresso in ms di polling per socket in ascolto */
#define SOCKET_ACTIVE_POLL 300
/** Tempo espresso in ms di polling per socket dormiente */
#define SOCKET_INACTIVE_POLL 1000

#define DEBUG_MASK 0

/** Inizializzazione dei valori nella modalità debug e non */
#ifdef DEBUG_MODE
    #undef DEBUG_MASK

    #define LOG_LEN 60
    
    /** Definizione valore di debug mask */
    #define DEBUG_MASK 1

    /** Abilitazione debug webview per stampare log provenienti da essa */
    // #define WEBVIEW_DEBUG // TODO: i lose long msg dispatch log but also console...
                             // TODO: is env the right place?

    /** Abilitazione della console su windows per stampare i log */
    #define WIN_CONSOLE

    /** Abilitazione dello stream di uscita su cerr (per log errori) oltre che cout */
    // #define LOG_CERR

#endif

// Environment mismatch if changing SERVER_MACRO
//      either use function and object file (kind of logger method)
//      either use make file check env
//      either define server host in wscustom.cc (only where neededs)
#ifdef SERVER_REMOTE
    const std::string SERVER_HOST = "137.74.196.151:8000";
#else
    const std::string SERVER_HOST = "localhost:8000";
#endif

#endif