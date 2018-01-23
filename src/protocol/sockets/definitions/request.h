#ifndef PROTOCOL_SOCKET_DEFINITIONS_REQUEST_H
#define PROTOCOL_SOCKET_DEFINITIONS_REQUEST_H

#include <json.hpp>

using nlohmann::json;

namespace ws {

    namespace RequestDefinition {

        typedef struct Request {
            std::string AUTH;
            std::string content;
        } Request;

        Request createAuthenticated(std::string auth);
        Request createEmpty();

        void to_json(json& j, const Request& u);

        void from_json(const json& j, Request& u);

    }
}

#endif
