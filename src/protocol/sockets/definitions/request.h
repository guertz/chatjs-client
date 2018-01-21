#include <iostream>
#include <json.hpp>

using nlohmann::json;
using namespace std;

namespace ws {

    namespace RequestDefinition {

        typedef struct Request {
            string AUTH;
            string content;
        } Request;

        Request createAuthenticated(string auth);
        Request createEmpty();

        void to_json(json& j, const Request& u);

        void from_json(const json& j, Request& u);

    }
}
