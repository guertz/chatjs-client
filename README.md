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
* TDM-GCC 64 (mingw32-make, g++)

> Linux (tested on linux mint 18.2-cinnamon-64)
* build-essential (make, g++)
* libwebkit2gtk-4.0-dev

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
$ make depend
$ make
```

#### Using a remote server
> Si possono configurare host in env.h
```
$ make SERVER=remote
```

## Testing without a local server
> **Attenzione** Non è detto che il server sia sempre online e acceso.
La compilazione in modalità **remote server** predispone che la app si interfacci con un server remoto piuttosto che su localhost
permettendo così di provare l'applicazione senza necessariamente dover aver installato e lanciato il [server locale](https://github.com/Guertz/chatjs-server)
Utenti di test:
+ *devel*: bVENYJjcCe02Xrr8
+ *leved*: 541YRimIyKmgOqbE

#### Available log levels
> Le maschere di debug possono essere combinate per avere a disposizione più livelli di log contemporaneamente
**Sample**
> - Enable all logs &rarr; MASK = 7

```
+ pedantic      # MASK = 4
+ details       # MASK = 2
+ base          # MASK = 1
+ console       # sempre attivo in debug 
                # (invocato da JS window.consolelog)
```

## Documentation
```
$ doxygen
```
[Available online](https://guertz.github.io/chatjs-client/html/)

## Folder Structure
> Per una descrizione dettagliata dei vari file [fare riferimento qui](https://guertz.github.io/chatjs-client/html/files.html)
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
    ├── pages                           # Partials (chat-list, chat-details)
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
## Next steps
- [x] Code refactoring
- [ ] OSX platform & release build
- [ ] OOP (singleton & component will inherit states)
- [ ] Websocket/Events poll loops like libuv
- [ ] JavaScript document API binding
- [ ] Data Models refactoring with different API system