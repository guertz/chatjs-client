#ifndef DIRECTIVES_MODALS_MODALS_H
#define DIRECTIVES_MODALS_MODALS_H

/**
 * @brief Interfaccia Modals, modale per iniziareuna chat
 * @file modals.h
 */

/** Funzioni di supporto e metodi elementari e la gestione degli alert Modali. */
namespace Modals {

    /**
     * Raccolta di funzioni utili per visualizzare e nascondere modal
     * identificati da una parola chiave
     */
    namespace Events {
        /**
         * Mostra un modale.
         * @param[in] args Identificativo del modale da visualizzare 
         */
        void ShowModalByRef(const std::string& args);
        
        /**
         * Nasconde un modale.
         * @param[in] args Identificativo del modale da nascondere 
         */
        void HideModalByRef(const std::string& args);
    }

    /**
     * Inizializza i componenti Modali quali:
     * + ::Modals::AuthModal
     * + ::Modals::ChatModal
     */
    void Bootstrap();

    /**
     * Distrugge i componenti Modali
     */
    void Destroy();

}
 
#endif