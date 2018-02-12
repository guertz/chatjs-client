#ifndef COMPONENTS_TOAST_TOAST_H
#define COMPONENTS_TOAST_TOAST_H

/**
 * @brief Interfaccia Toast, sistema di comunicazione notifiche 
 * @file toast.h
 */

/** Funzioni di supporto per mostrare un alert di tipo Toast. */
namespace Toast {
    
    /** Spazio dei nomi per funzioni gestione alert di tipo Toast */
    namespace Events {

        /**
         * Metodo per mostrare un alert di tipo toast che scompare automaticamente 
         * dopo 3 secondi.
         *
         * @param[in] args Contenuto da visualizzare all'interno dell'alert Toast
         *
         */
        void Show(const std::string& args);
    }

    /** Metodo di inizializzazione toast alert */
    void Bootstrap();
}

#endif