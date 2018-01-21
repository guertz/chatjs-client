#include <iostream>
#include <json.hpp>
#include "request.h"

using nlohmann::json;
using namespace std;

namespace ws {

    namespace RequestDefinition {

        Request createAuthenticated(string auth) {
            Request base { auth, "{}" };

            return base;
        }

        Request createEmpty() {
            return createAuthenticated("");
        }

        void to_json(json& j, const Request& u) {
            j = json{ 
                    { "AUTH", u.AUTH },
                    { "content", json::parse(u.content) }
                };
        }

        void from_json(const json& j, Request& u) {
            u.AUTH = j.at("AUTH").get<string>();
            u.content = j.at("content").dump();
        }

    }
}
