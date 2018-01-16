/** 
 * Funzioni di supporto per mostrare un alert di tipo Toast
 * sulla finestra.
 */
namespace Toast {

    namespace Events {
        /**
         * Mostra un alert di tipo toast che scompare automaticamente 
         * dopo 3 secondi.
         * @param[in] argc Contenuto da visualizzare all'interno dell'alert Toast
         *
         */
        void Show(const char* argc);
    }
}