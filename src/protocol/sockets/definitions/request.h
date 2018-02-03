#ifndef PROTOCOL_SOCKET_DEFINITIONS_REQUEST_H
#define PROTOCOL_SOCKET_DEFINITIONS_REQUEST_H

#include <iostream>
#include <json.hpp>
#include "models/json-item.h"

namespace ws {

    class BaseRequest : public JsonItem {

        public:
            std::string AUTH;
            std::string content;
        
            BaseRequest();
            BaseRequest(const std::string& serialized);
            BaseRequest(const nlohmann::json& j);

            
            nlohmann::json to_json() const;
            
    };
}

#endif
