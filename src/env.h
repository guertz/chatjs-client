/** Definizione url websocket per server remoto */
#define SERVERHOST "137.74.196.151:8000"

/** Definizione url websocket per server locale */
#define LOCALHOST  "localhost:8000"

#ifdef SERVER_REMOTE
    #define APPURL SERVERHOST
#else
    #define APPURL LOCALHOST
#endif