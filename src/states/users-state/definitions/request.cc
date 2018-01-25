#include "request.h"

using json = nlohmann::json;
using namespace std;

namespace States {
    namespace UsersState {

        namespace Request {
            Stream::Stream() {
                this->type = STREAMSIGNAL::CLOSE;
            }

            Stream::Stream(const json& j) : Stream() {
                this->from_json(j);
            }

            Stream::Stream(const string& serialized) : Stream() {
                this->from_json(json::parse(serialized));
            }

            // si presume sia nel formato corretto
            void Stream::from_json(const json& j) {
                this->type = str_to_enum(j.at("type").get<string>());
            }

            json Stream::to_json() {
                return json{
                    { "type", enum_to_str(this->type)}
                };
            }

            string Stream::serialize() {
                return this->to_json().dump();
            }
        }
    }
}