#include "request.h"

using json = nlohmann::json;
using namespace std;

namespace States {
    namespace AuthState {

        namespace Request {
            Auth::Auth() {
                this->type = AUTHSIGNAL::ALL;
                this->user = "";
            }

            Auth::Auth(const json& j) : Auth() {
                this->from_json(j);
            }

            Auth::Auth(const string& serialized) : Auth() {
                this->from_json(json::parse(serialized));
            }

            // si presume sia nel formato corretto
            void Auth::from_json(const json& j) {
                this->type = str_to_enum(j.at("type").get<string>());
                this->user = j.at("user").get<string>();
            }

            json Auth::to_json() {
                return json{
                    { "type", enum_to_str(this->type)}, 
                    { "user", this->user }
                };
            }

            string Auth::serialize() {
                return this->to_json().dump();
            }
        }
    }
}