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
     * Spazio dei nomi relativo agli eventi generati da callbacks. Esempi 
     * sono lo stato dell'autenticazione utente.
     */
    namespace State {
        /** 
        * Metodo che ascolta in tempo reale eventi riguardanti l'autenticazione.
        * Dopo essere stato registrato viene notificato dal corrispondente provider
        * di eventuali cambiamenti di stato quali azioni di login e di logout
        *
        * Formato json evento authstate con parametri base
        * @include auth/auth-base.json
        *
        * Formato json evento authstate con parametri login
        * @include auth/auth-extended.json
        *
        * @param[in] argc Stringa json serializzata contenente le informazioni riguardanti
        * il cambio di stato
        */
        void Auth(const char* argc);
    }
}