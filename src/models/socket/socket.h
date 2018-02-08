#ifndef MODELS_SOCKET_SOCKET_H
#define MODELS_SOCKET_SOCKET_H

#include <iostream>
#include <json.hpp>
#include "models/json-item.h"

/**
 * @brief Interfaccia modelli Socket (Json): BaseRequest, BaseResponse.
 * @file socket.h
 */

namespace ws {

    // TODO: template classes
    // TODO: error dispatcher
    
    /** Interfaccia classe BaseRequest per socket communication (Json)  */
    class BaseRequest : public JsonItem {

        public:
            std::string AUTH; /**< Chiave di autenticazione utente per richiesta */
            std::string content; /**< Contenuto della richiesta in formato json serializzato string */
        
            BaseRequest(); /**< Costruttore di default che inizializza con stringhe vuote. */
            BaseRequest(const std::string& serialized); /**< Costruttore da oggetto json */
            BaseRequest(const nlohmann::json& j); /**< Costruttore da oggetto Json serializzato (string) */
            ~BaseRequest();
            
            nlohmann::json to_json() const;
            
    };

    /** Interfaccia classe BaseResponse per socket communication (Json)  */
    class BaseResponse : public JsonItem {

        public:
            bool ok; /**< Valore che indica se la risposta ha avuto esito positivo o no */
            int status; /**< Valore che indica lo stato/esito della risposta */
            std::string content; /**< Contenuto della risposta in formato json serializzato string */
            std::string error; /**< Messaggio di errore della risposta */

            BaseResponse(); /**< Costruttore che inizializza ai valori di default */
            BaseResponse(const nlohmann::json& j); /**< Costruttore da oggetto json */
            BaseResponse(const std::string& serialized); /**< Costruttore da oggetto Json serializzato (string) */
            ~BaseResponse();

            nlohmann::json to_json() const;

    };
}

#endif