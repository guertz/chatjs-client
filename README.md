# Chatjs - a minimal Chat application
icons

## A short description
Chatjs, è un'applicazione C++ di chat in tempo reale, cross-platform dotata di interfaccia grafica realizzata in linguaggio di markup HTML e renderizzata sui browser engine nativi del dispositivo. 
Si interfaccia con un server di backend in nodejs tramite WebSockets con scambio di messaggi in formato JSON.
Per mettere in comunicazione i componenti fa uso di un sistema di callback basato sui puntatori a funzione.

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
## Next steps
+ OOP
    - state are an extension of components
    - Singleton class concepts

+ Optimize poll loops like libuv
+ Picodom JS template library
+ Gulp inject for serving and testing in browser to develop interfaces

## Requirements
+ C++11
+ Nodejs to compile GUI  

# To compile on windows:
tdm-gcc 64  
advice: git bash
# To compile on linux (ubuntu tested):
build-essentials (make, g++)
webkit-gtk

for mor platform see github

## Steps:


# Troubleshoot
No nodejs?
.tmp is a swap of last compiled assets
gulp fake tools based on platform under tools/ could be used as aliases
Directory personalizzate da www/.bundle devono essere specificate negli script