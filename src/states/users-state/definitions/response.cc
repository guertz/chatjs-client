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

            Stream::Stream(const json& j) : Stream() {
                this->from_json(j);
            }

            Stream::Stream(const string& serialized) : Stream() {
                this->from_json(json::parse(serialized));
            }

            void Stream::from_json(const json& j) {
                this->type = str_to_enum(j.at("type").get<string>());
                this->usersList = j.at("usersList").dump();
            }

            json Stream::to_json() {
                return json{
                    { "type", enum_to_str(this->type)}, 
                    { "usersList", json::parse(this->usersList)}
                };
            }

            string Stream::serialize() {
                return this->to_json().dump();
            }

        }

    }
}