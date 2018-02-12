#ifndef COMPONENTS_NAVBAR_NAVBAR_H
#define COMPONENTS_NAVBAR_NAVBAR_H

/**
 * @brief Interfaccia Navbar, menù di navigazione superiore 
 * @file navbar.h
 */

/** 
 * Funzioni di supporto e metodi elementari e la gestione
 * delle voci presenti nella barra di navigazione superiore
 */
namespace Navbar {

    /**
     * Inizializza le voci del menu, quali:
     * + ::Navbar::Profile
     */
    void Bootstrap();

    /** Distrugge le voci del menù */
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
        inline void Auth();
    }
}

#endif