#ifndef PROTOCOL_SOCKETS_DEFINITIONS_RESPONSE_H
#define PROTOCOL_SOCKETS_DEFINITIONS_RESPONSE_H

#include <iostream>
#include <json.hpp>

namespace ws {

    class BaseResponse {
        private:
            void from_json(const nlohmann::json& );

        public:
            bool ok;
            int status;
            std::string content;
            std::string error;

            BaseResponse();
            BaseResponse(const nlohmann::json& j);
            BaseResponse(const std::string& serialized);

            nlohmann::json to_json();
            std::string serialize();

    };
}

#endif