#ifndef DIRECTIVES_MODALS_MODALS_H
#define DIRECTIVES_MODALS_MODALS_H

/** 
 * Funzioni di supporto e metodi elementari e la gestione
 * degli alert Modali. 
 */
namespace Modal {

    /**
     * Inizializza i componenti Modali quali:
     * + AuthModal
     * + ChatModal
     */
    void Bootstrap();

    /**
     * Distrugge i componenti Modali
     */
    void Destroy();

    /**
     * Raccolta di funzioni utili per visualizzare e nascondere modal
     * identificati da una parola chiave
     */
    namespace Events {
        /**
         * Mostra un modale.
         * @param[in] argc Identificativo del modale da visualizzare 
         */
        void ShowModalByRef(const std::string& argc);
        /**
         * Nasconde un modale.
         * @param[in] argc Identificativo del modale da nascondere 
         */
        void HideModalByRef(const std::string& argc);
    }

}
 
#endif