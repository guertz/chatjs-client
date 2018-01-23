#ifndef PROTOCOL_SOCKETS_DEFINITIONS_RESPONSE_H
#define PROTOCOL_SOCKETS_DEFINITIONS_RESPONSE_H

#include <json.hpp>
using nlohmann::json;

namespace ws {

    namespace ResponseDefinition {

        typedef struct Response {
            bool ok;
            int status;
            std::string content;
            std::string error;
        } Response;

        void to_json(json& j, const Response& u);

        void from_json(const json& j, Response& u);

    }
}

#endif