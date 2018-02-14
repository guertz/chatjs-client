/** 
 * @file components.h
 * @brief Breve descrizione della struttura di un componente
 *
 * Per un componente generico è possibile notare in comune:
 * + La presenza di un file .js.h contente una stringa di tipo R (raw literals) che contiene la logica Javascript del componente
 * + Namespace interni:
 *  - **Events**: per metodi che effettuano cambiamenti all'interfaccia (Hanlder/Dispatcher)
 *  - **State**: per i metodi che fungono da callback per eventi di cambiamento allo stato dei dati.  I metodi sono del tipo `inline` con la convenzione di essere chiamati *Auth* per *AuthState* o *Chat* per *ChatState*
 *  - **&lt;State&gt;Methods**: per i metodi di supporto di un determinato state dei dati: *Auth* può avere in questa sezione i metodi `OnLoginSuccess`, `OnLoginError`. Sono inseriti in questa sezione per non sporcare altri parti del codice.
 * + Metodi comuni:
 *  - **Bootstrap**: che funge da costruttore (Carica il componente Javascript nel file .js.h e registra eventi di callback)
 *  - **Destroy**: che funge da distruttore
 * + Variabili: eventuale variabili a livello di componente vengono dichiarate nel proprio namespace e identificate dalla parola chiave `static`
 *
 * Un esempio della struttura è qui riportato:
 * ```
 *
 * namespace App {
 * 
 *  namespace Events { 
 *      inline void Cb_name(const std::string& args);
 *  }
 *
 *   // Metodo che funge da costrutture (per inizializzazioni)
 *   void Bootstrap();
 *
 *   // Metodo che funge da distruttore
 *   void Destroy();
 * }
 * 
 * ``` 
 */