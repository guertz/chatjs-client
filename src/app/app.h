#ifndef APP_APP_H
#define APP_APP_H

/**
 * Componente principale incaricato della gestione delle varie parti dell'
 * applicazione. Le parti sono suddivise in:
 * + Pagine (pages),
 * + Servizi (providers),
 * + Direttive (navbar, modals...)
 *
 * Pagine e direttive sono entrambe considerate componenti in un modo più
 * generico
 */
namespace App {
    /**
     * Spazio dei nomi in cui vengono registrati gli eventi che vanno ad interagire
     * sulla finestra. Vengono ragruppati gli eventi che provengono da entrambe le
     * direzioni ovvero:
     * + Invocazione di metodi C++ che richiamano funzioni Javascript
     * + Invocazioni dal Javascript a metodi C++
     */
    namespace Events { 
        /**
         * Metodo invocato da JavaScript che notifica il caricamento avvenuto degli
         * script e degli stili.
         * @param[in] args Parametri della chiamata JS in formato JSON serialized
         * @return void
         */
        void Ready(const std::string& args);
    }

    /**
     * Metodo della registrazione del componente App.
     * Registra gli eventi di callback javascript:
     * + Ready
     */
    void Bootstrap();

    /**
     * Metodo della distruzione del componente App.
     * Notifica tutti i sotto-componenti e servizi inizializzati
     */
    void Destroy();
}

#endif