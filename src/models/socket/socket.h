#ifndef MODELS_SOCKET_SOCKET_H
#define MODELS_SOCKET_SOCKET_H

#include <iostream>
#include <json.hpp>
#include "models/json-item.h"

/**
 * @brief Interfaccia modelli Socket (Json): ws::BaseRequest, ws::BaseResponse.
 * @file socket.h
 */

namespace ws {

    // TODO: template classes
    // TODO: error dispatcher
    
    /** Interfaccia classe ws::BaseRequest per socket communication (Json)  */
    class BaseRequest : public JsonItem {

        public:
            std::string AUTH; /**< Chiave di autenticazione utente per richiesta */
            std::string content; /**< Contenuto della richiesta in formato json serializzato string */
        
            BaseRequest();
            BaseRequest(const std::string& serialized);
            BaseRequest(const nlohmann::json& j);
            ~BaseRequest();
            
            nlohmann::json to_json() const;
            
    };

    /** Interfaccia classe ws::BaseResponse per socket communication (Json)  */
    class BaseResponse : public JsonItem {

        public:
            bool ok; /**< Valore che indica se la risposta ha avuto esito positivo o no */
            int status; /**< Valore che indica lo stato/esito della risposta */
            std::string content; /**< Contenuto della risposta in formato json serializzato string */
            std::string error; /**< Messaggio di errore della risposta */

            BaseResponse(); 
            BaseResponse(const nlohmann::json& j); 
            BaseResponse(const std::string& serialized); 
            ~BaseResponse();

            nlohmann::json to_json() const;

    };
}

#endif