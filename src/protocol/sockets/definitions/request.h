#ifndef PROTOCOL_SOCKET_DEFINITIONS_REQUEST_H
#define PROTOCOL_SOCKET_DEFINITIONS_REQUEST_H

#include <iostream>
#include <json.hpp>

namespace ws {

    class BaseRequest {
        private:
            void from_json(const nlohmann::json& );

        public:
            std::string AUTH;
            std::string content;
        
            BaseRequest();
            BaseRequest(const std::string& serialized);
            BaseRequest(const nlohmann::json& j);

            
            nlohmann::json to_json();
            std::string serialize();
            
    };
}

#endif
