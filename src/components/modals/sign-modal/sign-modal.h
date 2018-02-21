#ifndef COMPONENTS_MODALS_SIGN_MODAL_SIGN_MODAL_H
#define COMPONENTS_MODALS_SIGN_MODAL_SIGN_MODAL_H

/**
 * @brief Interfaccia SignModal, modale per registrarsi
 * @file sign-modal.h
 */

namespace Modals {

   /** Modale che permette ad un utente di registrarsi */
    namespace SignModal {

       /**
        * Spazio dei nomi in cui vengono registrati gli eventi che vanno ad interagire
        * sulla finestra.
        */
        namespace Events {

            /** Metodo per mostrare il modale */
            void Show();

            /** Metodo per nascondere il modale */
            void Hide();

        }

        /** Metodo di inizializzazione del modale */
        void RegisterModal();

        /** Metodo di distruzione del modale */
        void EraseModal();
        
    }
}

#endif