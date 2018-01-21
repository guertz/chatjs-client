// put all #define here
// login action is commented
// refactor main.cc
// file name kamel case convenction
// macro to include??
//refactor json samples format
// const char* => use string when i can!!
// header ifdef, define, ifndef
// make pointer more resistant (assets)
// comments on files are safe?
// everything as a string

#define SERVER_HOST "localhost"
#define SERVER_PORT "8000"
#define SOCKET_ACTIVE_POLL 300
#define SOCKET_INACTIVE_POLL 1000

// DEFAULT
// #define WEBVIEW_DEBUG 0
// #define DEBUG_MASK 0

#ifdef DEBUG_MODE

    // DEFAULT WITH DEBUG
    //  Cannot set from make file, only here
    #define DEBUG_MASK 1
    #define WEBVIEW_DEBUG 0

#endif



