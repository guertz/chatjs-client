#include <iostream>
#include <json.hpp>

using nlohmann::json;
using namespace std;

namespace ws {

    namespace ResponseDefinition {

        typedef struct Response {
            bool ok;
            int error;
            string content;
        } Response;

        void to_json(json& j, const Response& u);

        void from_json(const json& j, Response& u);

    }
}