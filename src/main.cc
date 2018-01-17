/**
 * @mainpage Chat.js
 *
 * @author Matteo Guerzoni
 *
 * Esempio di chat in C++ realizzata attraverso tecnologie ibride e websockets.  
 * Chat.js è una dimostrazione di come il C++ possa essere un linguaggio da  
 * considerarsi alla pari dei "moderni linguaggi".
 *
 * Attraverso la libreria webview realizzata da zserge e disponibile su github  
 * è stato possibile realizzare la User Interface in modo più semplice tramite  
 * i linguaggi HTML, JavaScript per gestire gli eventi notificati ad appositi  
 * metodi C++ incaricati delle fasi di elaborazione ed infine CSS per  
 * realizzare lo stile. 
 *
 * L'interoperabilità tra i vari componenti e metodi (C++/JS JS/C++ C++/C++)  
 * è stata resa possibile attraverso lo scambio di messaggi in formato JSON  
 * serializzato sotto forma di stringa. Infine l' applicazione comunica  
 * tramite la libreria easywsclient realizzata da dhbaird (sempre reperibile  
 * su github) con un server realizzato in nodejs incaricato di gestire la  
 * logica di un servizio di chat in tempo reale.  
 *
 * L'obiettivo è stato raggiunto ed è stata realizzata un applicazione  
 * realtime multipiattaforma leggera e che richiede pochissime dipendenze.  
 * Il lavoro tuttavia non è ancora completato e verrà portato avanti per  
 * per realizzare una struttura ancora più rigida e indipendente dal JS  
 * orientata ad oggetti
 * 
 * Vai alla definizione del file ::main 
 */

// Librerie per la funzionalità dei websocket richieste dalle piattaforme windows
#ifdef WIN32
  // #pragma comment( lib, "ws2_32" )
  #include <WinSock2.h>
#endif

#include <iostream>
#include <assert.h>
#include "common/web-ui/web-ui.h"
#include "app/app.h"

using namespace std;
using namespace WebUI;


// TODO: che sistema usa zserge per il log negli ambienti gui
//       dove le shell non compaiono?
//       serve il win main?
int main() {
  #ifdef WIN32
    // Aggancia il terminale su windows per poter aver accesso ai log
    if(AttachConsole(ATTACH_PARENT_PROCESS) || AllocConsole()){
      freopen("CONOUT$", "w", stdout);
      freopen("CONOUT$", "w", stderr);
    }

    // Configurazione socket aggiuntive richieste dalle piattaforme windows
    INT rc;
    WSADATA wsaData;

    rc = WSAStartup(MAKEWORD(2, 2), &wsaData);

    // TODO: validate if rc!=0

    cout<<endl;
  #endif

  // Move all to app bootstrap?
  Webview* webview = Create(); // WebUI::Create => Inizializzazione webview
  
  App::Bootstrap(); // Metodo inizializzare la app
                    // Aspetterà a sua volta l'invocazione del callback di ready
                    // Per caricare tutte le altre sezioni e componenti
  
  Inject(); // WebUI::Inject => Injecting dello stile e degli script JS
            // Inserito dopo App::Bootstrap perchè bootstrap registra il metodo
            // di callback Ready invocato dopo aver iniettato queste risorse

  while (webview_loop(webview, 1) == 0) 
      ; // Application Loop

  webview_exit(webview);

  App::Destroy(); // Metodo Distruttore
  
  #ifdef WIN32
    WSACleanup(); // Necessario sulle piattaforme windows
                  // per terminare i socket
  #endif

  return 0;
}