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
 * Per sfogliare la documentazione, è consigliato partire dal metodo ::main  
 * per poi continuare nelle due sezione:
 * + Webview User Interface (::WebUI): in cui sono definiti i metodi principali  
 * per la gestione della webview e a sua volta dell'interfaccia utenti
 * + App (::App): in cui sono definiti i metodi e i moduli che compongono  
 * l'applicazione stessa
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


int main() {
  #ifdef WIN32
  
    #ifdef WIN_CONSOLE
      // Aggancia il terminale su windows per poter aver accesso ai log
      if(AttachConsole(ATTACH_PARENT_PROCESS) || AllocConsole()){
        freopen("CONOUT$", "w", stdout);
        freopen("CONOUT$", "w", stderr);
      }
    #endif

    // Configurazione socket, API WIN32
    INT rc;
    WSADATA wsaData;

    rc = WSAStartup(MAKEWORD(2, 2), &wsaData);

    assert(!rc);

  #endif

  Webview* webview = WebUI::Create(); // Inizializzazione webview
  
  App::Bootstrap(); // Metodo inizializzare moduli e componenti
                    // dell'applicazione
  
  WebUI::Inject(); // Vengono caricate le risorse di base 
                   // (HTML, stili css, metodi Javascript)

  log_csl("Main", "Entering application loop [Running]");
  while (webview_loop(webview, 1) == 0) 
      ; // Application Loop (blocking)

  log_csl("Main", "Exit application loop [Exit]");
  webview_exit(webview);

  App::Destroy(); // Metodo Distruttore
  
  #ifdef WIN32
    WSACleanup(); // Chiusura/pulizia socket, API WIN32
  #endif

  return 0;
}