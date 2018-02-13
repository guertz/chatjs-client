#ifndef MODELS_JSONITEM_H
#define MODELS_JSONITEM_H

#include <json.hpp>

/**
 * @brief Interfaccia classe Json, base per oggetti di tipo Json 
 * @file json-item.h
 */

/** Classe base da implementare per oggetti di tipo Json */
class JsonItem {

    public:
    
        /**
         * Metodo per trasformare l'oggetto in formato json
         *
         * @return Oggetto Json rappresentativo della classe
         */
        virtual nlohmann::json to_json() const;

        /**
         * Metodo per trasformare l'oggetto in formato stringa (json serializzato)
         *
         * @return stringa serializzata json rappresentativo della classe
         */
        std::string serialize() const;
        

};


#endif