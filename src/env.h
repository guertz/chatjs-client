#ifndef ENV
#define ENV
/**
 *  @brief  Variabili d'ambiente condivise.
 */

/** Tempo espresso in ms di polling per socket in ascolto */
#define SOCKET_ACTIVE_POLL 300
/** Tempo espresso in ms di polling per socket dormiente */
#define SOCKET_INACTIVE_POLL 1000

// const unsigned int MESSAGES   = 10;
/** Inizializzazione dei valori nella modalità debug e non */
#ifdef DEBUG_MODE

    #define LOG_LEN 60

    /** Definizione valore di debug mask */
    #define DEBUG_MASK 1
    /** Abilitazione debug webview per stampare log provenienti da essa */
    // #define WEBVIEW_DEBUG // TODO: i lose long msg dispatch log but also console...
                             // TODO: is env the right place?
    /** Abilitazione della console su windows per stampare i log */
    #define WIN_CONSOLE

    /** Abilitazione dello stream di uscita su cerr (per log errori) oltre che cout*/
    // #define LOG_CERR

    /*
     * Stringhe contenenti dati del server (host, port) per ambiente 
     * locale (presupposto dalla debug mode)
     */   
    const std::string SERVER_HOST = "localhost";
    const std::string SERVER_PORT = "8000";

#else

    /** Defizione della DEBUG_MASK al valore 0 (disabilitata) */
    #define DEBUG_MASK 0

    /*
     * Stringhe contenenti dati del server (host, port) per ambiente 
     * release
     */   
    const std::string SERVER_HOST = "137.74.196.151";
    const std::string SERVER_PORT = "8000";

#endif
#endif