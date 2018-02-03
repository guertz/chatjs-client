#ifndef DIRECTIVES_NAVBAR_NAVBAR_H
#define DIRECTIVES_NAVBAR_NAVBAR_H

#include "states/auth-state/auth-state.h"

/** 
 * Funzioni di supporto e metodi elementari e la gestione
 * delle voci presenti nella barra di navigazione superiore
 */
namespace Navbar {

    /**
     * Inizializza le voci del menu, quali:
     * + Profilo
     */
    void Bootstrap();

    /**
     * Distrugge le voci del menu
     */
    void Destroy();

   /** 
    * Metodo che ascolta in tempo reale eventi riguardanti l'autenticazione.
    * Dopo essere stato registrato viene notificato dal corrispondente provider
    * di eventuali cambiamenti di stato quali azioni di login e di logout
    */
    namespace State {
        
       /** 
        * Metodo che ascolta in tempo reale eventi riguardanti l'autenticazione.
        * Dopo essere stato registrato viene notificato dal corrispondente provider
        * di eventuali cambiamenti di stato quali azioni di login e di logout
        */
        void Auth();
    }
}

#endif