#define SOCKET_ACTIVE_POLL 300
#define SOCKET_INACTIVE_POLL 1000

#ifdef DEBUG_MODE

    #define DEBUG_MASK 7
    #define WEBVIEW_DEBUG
    #define WIN_CONSOLE

#else
    #define DEBUG_MASK 0
#endif


#ifndef SERVER_ENV_ATTRIBUTES
#define SERVER_ENV_ATTRIBUTES
const unsigned int MESSAGES   = 10;

    #ifdef DEBUG_MODE
        const std::string SERVER_HOST = "localhost";
        const std::string SERVER_PORT = "8000";
    #else
        const std::string SERVER_HOST = "137.74.196.151";
        const std::string SERVER_PORT = "8000";
    #endif
#endif


