#ifndef MODELS_USER_USER_H
#define MODELS_USER_USER_H

#include <iostream>
#include <json.hpp>
#include "models/json-item.h"

/**
 * @brief Interfaccia classe User (Json) 
 * @file user.h
 */

/** Interfaccia classe User (Json)  */
class User : public JsonItem {

    public:
        std::string name; /**< Attributo nome utente */
        std::string image; /**< Attributo immagine utente */
        std::string _id; /**< Attributo user ID utente */

        User(); /**< Costruttore di default. */
        User(const nlohmann::json& j); /**< Costruttore da oggetto Json */
        User(const std::string& serialized); /**< Costruttore da oggetto Json serializzato (string) */
        ~User();

        nlohmann::json to_json() const;

        /**
         * Metodo che controlla se l'utente è valido
         *
         * @return bool Utente valido
         */
        bool is_valid() const;
};

#endif