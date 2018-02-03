#include "response.h"

using json = nlohmann::json;
using namespace std;

namespace States {
    namespace UsersState {
        namespace Response {

            Stream::Stream() {
                this->type = STREAMSIGNAL::CLOSE;
                this->usersList = "[]";
            }

            Stream::Stream(const json& j) {
                this->type = str_to_enum(j.at("type").get<string>());
                this->usersList = j.at("usersList").dump();
            }

            Stream::Stream(const string& serialized) 
                : Stream(json::parse(serialized)) { }

            json Stream::to_json() const {
                return json{
                    { "type", enum_to_str(this->type)}, 
                    { "usersList", json::parse(this->usersList)}
                };
            }

        }

    }
}