#include <iostream>
#include "response.h"

using namespace std;

namespace ws {

    namespace ResponseDefinition {

        void to_json(json& j, const Response& u) {
            j = json { 
                        { "ok", u.ok },
                        { "status", u.status }, 
                        { "error", u.error},
                        { "content", json::parse(u.content)}
                     };
        }


        void from_json(const json& j, Response& u)  {
            u.ok = j.at("ok").get<bool>();
            u.status = j.at("status").get<int>();
            u.error = j.at("error").get<string>();
            u.content = j.at("content").dump();
        }

    }
}