#ifndef COMMON_HELPERS_HELPERS_H
#define COMMON_HELPERS_HELPERS_H

/** Funzioni di supporto per la gestione di stringhe, puntatori, etc. */
namespace Helpers {    
    /** Funzioni di supporto per la gestione dei puntatori. */
    namespace safeptr{

        /** 
        * Distruzione di un blocco puntatore a carattere.
        * @param[in,out] kPtrChar Puntatore ad array di caratteri passato per riferimento da azzerare e distruggere
        * @return void
        */
        void free_block(const char*& kPtrChar);

        // Duplicato della precedente funzione per supportare non const-
        // TODO: Creare una soluzione simile ai template
        void free_block(char*& ptrChar);

        /**
        * Funzione wrapper di reinterpret da char a void.
        * Il puntatore del valore di ritorno punta allo stesso oggetto
        * puntato dal puntatore passato come parametro dato che la
        * funzione non esegue altro che un reinterpret_cast
        *
        * @param[in,out] voidPtrChar Puntatore ad array di caratteri char da reinterpretare in void
        * @return void*
        */
        void *serialize(char *voidPtrChar);

        /**
        * Funzione wrapper di reinterpret da void a char.
        * Il puntatore del valore di ritorno punta allo stesso oggetto
        * puntato dal puntatore passato come parametro dato che la
        * funzione non esegue altro che un reinterpret_cast
        *
        * @param[in,out] charPtrVoid Puntatore ad array di caratteri void da reinterpretare in char
        * @return char*
        */
        char *deserialize(void *charPtrVoid);

        const char* parse_asset(const char* );
        // TODO:
            // Gestione struct
            // Gestione json structure
            //               buffer
            //               Serializer/Deserializer
        
        // TODO: Wrapper semplificazioni
            // void* duplicate(const char* _v_argsc); => serialize(duplicate(__a__))
            // char* duplicate(const void* _c_argsv); => duplicate(deserialize(__a__))
            // void* duplicate(const void* _v_argsv); => serialize(duplicate(deserialize(__a__)))
    }

    /** Funzioni di supporto per la copia di array di caratteri. */
    namespace safestr{

        /**
        * Funzione helper per la creazione di un'array di caratteri inizializzato vuoto.
        *
        * @param[in] size Dimensione array di caratteri
        * @return char*
        */
        char *bufferizable(const unsigned int size);

        /**
        * Funzione helper per la duplicazione di un'array di caratteri.
        *
        * @param[in] kPtrChar Array di caratteri in ingresso
        * @return char*
        */
        char *duplicate(const char * const kPtrChar);
    }

    namespace js{

        /** 
        * Funzioni di supporto per la copia di una stringa in modo varidico.
        * @param[in] size Dimensione dell'array di carattere finale
        * @param[in] parts Il numero di argomenti (sotto-stringhe) di cui è composto
        * @param[in] part Argomenti variadici (sotto-stringhe) che compongono la stringa finale costruita
        * @return char*
        */
        char *compact(const unsigned int size, const unsigned int parts, const char *part...);

        void* prepare(const char * const kPtrChar);
        
    }
}

#endif