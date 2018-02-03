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

            Auth::Auth(const json& j) {
                this->type = str_to_enum(j.at("type").get<string>());
                this->user = j.at("user").get<string>();
            }

            Auth::Auth(const string& serialized) 
                : Auth(json::parse(serialized)) { }


            json Auth::to_json() const {
                return json{
                    { "type", enum_to_str(this->type)}, 
                    { "user", this->user }
                };
            }

        }
    }
}