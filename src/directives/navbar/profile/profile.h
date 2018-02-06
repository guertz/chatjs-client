#ifndef DIRECTIVES_NAVBAR_PROFILE_PROFILE_H
#define DIRECTIVES_NAVBAR_PROFILE_PROFILE_H

/**
 * @brief Interfaccia Navbar/Profile, link profilo barra di navigazione
 * @file profile.h
 */

namespace Navbar {

    /** Voce del menù che consente all'utente di effettuare il logout. */
    namespace Profile {

        /** Spazio dei nomi relativo agli eventi per la voce Profilo del menù */
        namespace Events {

           /**
            * Handler di evento JavaScript che notifica evento di click sulla voce logout.
            *
            * @param[in] args Parametri della chiamata JS in formato JSON serialized.
            * Oggetto vuoto
            */
            inline void Disconnect(const std::string& args);

            /** Metodo per impostare il testo nella voce menù profilo  */
            void SetText(const std::string text);
        }

        /** Metodo di inizializzazione della voce del menù */
        void RegisterLink();

        /** Metodo per eliminare la voce del menù */
        void EraseLink();

    }
}

#endif