/**
 * @mainpage Chat.js
 *
 * @author Matteo Guerzoni
 *
 * Chatjs, è un'applicazione C++ di chat in tempo reale, cross-platform 
 * dotata di interfaccia grafica realizzata in linguaggio di markup HTML
 * e renderizzata sui browser engine nativi del dispositivo. 
 * Si interfaccia con un server di backend in nodejs tramite WebSockets 
 * con scambio di messaggi in formato JSON.
 * Per mettere in comunicazione i componenti fa uso di un sistema di callback 
 * basato sui puntatori a funzione.
 *
 * Gli eventi nella webview vengono mappati in c++ come callback a specifiche
 * funzioni che ricevono parametri in formato JSON serializzato e sono
 * bidirezionali nel senso che da C++ possono essere invocati metodi Javascript
 * e viceversa.
 * 
 * Vai alla definizione del file ::main 
 */

// Librerie per la funzionalità dei websocket richieste dalle piattaforme windows
#ifdef WIN32
  // #pragma comment( lib, "ws2_32" )
  #include <WinSock2.h>
#endif

#include <iostream>
#include <cassert>

#include "app/app.h"

#include "common/web-ui/web-ui.h"
#include "common/logger/logger.h"
#include "env.h"

using namespace std;
using namespace WebUI;


// TODO: che sistema usa zserge per il log negli ambienti gui
//       dove le shell non compaiono?
//       serve il win main?
// TODO: release && console non compare su linux giusto?
int main() {
  #ifdef WIN32
  
    #ifdef WIN_CONSOLE
      // Aggancia il terminale su windows per poter aver accesso ai log
      if(AttachConsole(ATTACH_PARENT_PROCESS) || AllocConsole()){
        freopen("CONOUT$", "w", stdout);
        freopen("CONOUT$", "w", stderr);
      }
    #endif

    // Configurazione socket aggiuntive richieste dalle piattaforme windows
    INT rc;
    WSADATA wsaData;

    rc = WSAStartup(MAKEWORD(2, 2), &wsaData);

    assert(!rc);

  #endif

  // Move all to app bootstrap?
  Webview* webview = Create(); // WebUI::Create => Inizializzazione webview
  
  App::Bootstrap(); // Metodo inizializzare la app
                    // Aspetterà a sua volta l'invocazione del callback di ready
                    // Per caricare tutte le altre sezioni e componenti
  
  Inject(); // WebUI::Inject => Injecting dello stile e degli script JS
            // Inserito dopo App::Bootstrap perchè bootstrap registra il metodo
            // di callback Ready invocato dopo aver iniettato queste risorse

  log_base("WEB", "loop");
  
  while (webview_loop(webview, 1) == 0) 
      ; // Application Loop

  log_base("WEB", "error");
  webview_exit(webview);

  App::Destroy(); // Metodo Distruttore
  
  #ifdef WIN32
    WSACleanup(); // Necessario sulle piattaforme windows
                  // per terminare i socket
  #endif

  return 0;
}