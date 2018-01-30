# Chatjs
> A minimal Chat application

## A short description
Chatjs, è un'applicazione C++ di chat in tempo reale, cross-platform dotata di interfaccia grafica realizzata in linguaggio di markup HTML e renderizzata sui browser engine nativi del dispositivo. 
Si interfaccia con un server di backend in nodejs tramite WebSockets con scambio di messaggi in formato JSON.
Per mettere in comunicazione i componenti fa uso di un sistema di callback basato sui puntatori a funzione.

## Prerequisites
* C++11

> Windows
* Git bash on windows (for Makefile commands)
* TDM-GCC 64

> Linux
* build-essentials (make, g++)
* webview (webkit-gtk)

## Dependencies
* [zserge/webview](https://github.com/zserge/webview)
* [nlohmann/json](https://github.com/nlohmann/json)
* [dhbaird/easywsclient](https://github.com/dhbaird/easywsclient)

## Compile
> Compilazione Makefile cross-platform

### Release
```
$ make ENV=release depend
$ make ENV=release
```

### Debug
```
$make depend
$make
```

#### Available log levels
> Le maschere di debug possono essere combinate per avere a disposizione più livelli di log contemporaneamente (ex. ALL = 7)

+ pedantic          # MASK = 4
+ details           # MASK = 2
+ base              # MASK = 1  
+ console           # sempre attivo in debug 
                    # (invocato da JS window.consolelog)

## Documentation
```
$ doxygen
```
[Available online](https://guertz.github.io/chatjs-client/html/)

## Folder Structure
```
├── .release                            # Release files & platform build
├── assets                              # Assets file (HTML/JS/CSS)
├── dependencies                        # Dependencies
├── docs                                # Documentation files
└── src                                 # Source files
    ├── app                             # App main/bootstrapper
    ├── common                          # Utilities (helper, logger, ...)
    │   ├── ...                         #
    ├── directives                      # Directives
    │   ├── modals                      # Modals (auth, chat, ...)
    │   │   ├── ...                     #
    │   ├── navbar                      # Navbar links (profile, ...)
    │   │   └── ...                     #
    │   └── toast                       # Toast
    ├── models                          # Data models
    │   └── ...                         #
    ├── pages                           # Components (chat-list, chat-details)
    │   ├── ...                         #
    ├── protocol                        # Protocolli di comunicazione
    │   └── sockets                     # Definizione Socket 
    │       ├── ...                     #
    └── states                          # Data providers
        ├── auth-state                  # Provider auth data
        │   └── ...                     #       
        ├── chat-state                  # Provider chat data
        │   └── ...                     #
        └── users-state                 # Provider users data
            └── ...                     #
```
## TODO
- [x] State refactoring
- [ ] OOP (singleton & component will inherit states)
- [ ] Websocket/Events poll loops like libuv
- [ ] JavaScript document API binding
- [ ] Data Models refactoring with different API system