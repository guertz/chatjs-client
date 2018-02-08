#ifndef MODELS_AUTH_AUTH_H
#define MODELS_AUTH_AUTH_H

#include <iostream>
#include <json.hpp>
#include "models/json-item.h"
#include "models/user/user.h"

/**
 * @brief Interfaccia modelli data Auth (Json, enums): AUTHSIGNAL, AuthRequest, AuthResponse.
 * @file auth.h
 */


/** Enum identificativo del tipo di azione che si sta compiendo. */
enum AUTHSIGNAL {
    LOGOUT = 0, /**< Enum per azione di logout */
    LOGIN  = 1, /**< Enum per azione di login */  
    ALL    = 2  /**< Enum per caso generale, solitamente errore */
};

/** Metodo per trasformare il valore string passato dal server in enum AUTHSIGNAL */
AUTHSIGNAL str_to_enum(const std::string& AUTH_ACTION);
/** Metodo per trasformare il valore enum AUTHSIGNAL passato in string */
std::string enum_to_str(const AUTHSIGNAL AUTH_ACTION);

/** Interfaccia classe AuthRequest (Json)  */
class AuthRequest : public JsonItem {
    
    public:
        AUTHSIGNAL  type; /**< Identificativo azione da eseguire sul server. */
        std::string user; /**< Chiave identificativa utente per effettuare login (User ID) */
            //  TODO: change to _id (since it is auth_key)

       /**
        * Costruttore di default. Inizializza la classe con
        * chiave utente vuota e azione logout
        */
        AuthRequest(); 

        AuthRequest(const nlohmann::json& j); /**< Costruttore da oggetto json */
        AuthRequest(const std::string& serialized); /**< Costruttore da oggetto Json serializzato (string) */
        ~AuthRequest();

        nlohmann::json to_json() const;

};

/** Interfaccia classe AuthResponse (Json)  */
class AuthResponse : public JsonItem {

    public:
        AUTHSIGNAL type; /**< Identificativo azione da risposta del server. */
        User user; /**< Contenuto utente. valori di default se autenticazione fallisce. */
        bool online; /**< Campo che specifica se l'azione di login è andata a buon file. */
        
        std::string error; /**< Campo che riporta gli errori verificatasi. */
        
       /**
        * Costruttore di default. Inizializza la classe con
        * logout, utente default, false e stringa vuota errori
        */
        AuthResponse();
        AuthResponse(const nlohmann::json& j); /**< Costruttore da oggetto json */
        AuthResponse(const std::string& serialized); /**< Costruttore da oggetto Json serializzato (string) */
        ~AuthResponse();

        nlohmann::json to_json() const;
        
};


#endif