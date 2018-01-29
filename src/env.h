#define SOCKET_ACTIVE_POLL 300
#define SOCKET_INACTIVE_POLL 1000

#ifdef DEBUG_MODE

    // DEFAULT WITH DEBUG
    // DEFAULT GENERAL?
    #define DEBUG_MASK 1
    #define WEBVIEW_DEBUG
    #define WIN_CONSOLE

#else
    #define DEBUG_MASK 0
#endif


#ifndef SERVER_ENV_ATTRIBUTES
#define SERVER_ENV_ATTRIBUTES
const unsigned int MESSAGES   = 10;
const std::string SERVER_HOST = "localhost";
const std::string SERVER_PORT = "8000";
#endif


