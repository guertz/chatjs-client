#ifndef PROTOCOL_SOCKETS_DEFINITIONS_RESPONSE_H
#define PROTOCOL_SOCKETS_DEFINITIONS_RESPONSE_H

#include <iostream>
#include <json.hpp>
#include "models/json-item.h"

namespace ws {

    class BaseResponse : public JsonItem {

        public:
            bool ok;
            int status;
            std::string content;
            std::string error;

            BaseResponse();
            BaseResponse(const nlohmann::json& j);
            BaseResponse(const std::string& serialized);

            nlohmann::json to_json() const;

    };
}

#endif