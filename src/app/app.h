#ifndef APP_APP_H
#define APP_APP_H

/**
 * @brief Interfaccia "Core" applicazione, gestisce i vari sotto-moduli.
 * @file app.h
 */
 
/**
 * Principalmente le parti che compongono l'intera applicazione sono:
 * + Componenti grafici (components.h). Sono i componenti percepiti e  
 *   con cui l'utente interagisce. Si suddividono in due categorie:
 *   - Partials ovvero componenti ben definiti e presenti per
 *     tutto il ciclo di vita dell'applicazione:
 *     - ::ChatDetails
       - ::ChatList
 *   - Direttive ovvero componenti dinamici che non hanno una
 *     struttura rigida, ma che invece possono essere personalizzati
 *     e compaiono in determinati momenti o per determinate azioni:
 *     - ::Toast
 *     - ::Navbar
 *     - ::Modals
 * + Data states (States). Si tratta della gestione dei dati, da come
 *   ottenere questi ultimi e alla struttura dati per come salvarli:
 *   - Data models. Struttura di un dato e come quest'ultimo viene
 *     rappresentato in memoria. In questo esempio di applicazione
 *     i dati sono principalmente tutte classi con attributi pubblici
 *     (Simile al concetto di struct ma con l'aggiunta di metodi per
 *     codificare/decodificare dati nel formato JSON.
 *     I tipi di dato base o condivisi sono presenti sotto la directory (/models)
 *     mentre quelli interni e più specializzati sono in apposite cartelle
 *     denominate (definitions/) e richiedono un necessario utilizzo dei namespace.
 *     - ::JsonItem definizione modello data JSON base
 *   - Data provider (/states). Fungono da contenitore per immagazzinare/caricare
 *     dati da fonti esterne (socket) e mantenerli in un formato consistente
 *     notificando di cambiamenti altri eventuali componti che ne fanno attraverso
 *     un sistema di callback.
 *     - ::States::AuthState
 *     - ::States::ChatsState
 *     - ::States::UsersState
 */
namespace App {
    /**
     * Spazio dei nomi in cui vengono registrati gli eventi che vanno ad interagire
     * sulla finestra. Vengono ragruppati gli eventi che provengono da entrambe le
     * direzioni ovvero:
     * + Invocazione di metodi C++ che richiamano funzioni Javascript
     * + Invocazioni dal Javascript a metodi C++ (metodi inline).
     *   La parola chiave **inline** sopperisce alla mancanza di una programmazione
     *   orientata ad oggetti in cui questi metodi potrebbero essere definiti come private.
     */
    namespace Events { 
        /**
         * Handler di evento JavaScript che notifica il caricamento avvenuto degli
         * script e degli stili.
         *
         * Provvede ad inizializzare le dipendenze (servizi, altri componenti)
         *
         * @param[in] args Parametri della chiamata JS in formato JSON serialized
         */
        inline void Ready(const std::string& args);
    }

    /**
     * Metodo della registrazione del componente App.
     * Registra gli eventi di callback javascript:
     * + Ready
     * Registra i vari servizi
     */
    void Bootstrap();

    /**
     * Metodo della distruzione del componente App.
     * Notifica tutti i sotto-componenti e servizi inizializzati
     */
    void Destroy();
}

#endif