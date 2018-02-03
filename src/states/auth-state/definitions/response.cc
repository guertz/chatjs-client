#include "response.h"

using json = nlohmann::json;
using namespace std;

namespace States {
    namespace AuthState {
        namespace Response {

            Auth::Auth() {
                this->type = AUTHSIGNAL::ALL;
                this->online = false;
                // this->user // default constructor
            }

            Auth::Auth(const json& j) {
                this->type = str_to_enum(j.at("type").get<string>());
                this->online = j.at("online").get<bool>();
                this->user   = User(j.at("user"));
            }

            Auth::Auth(const string& serialized)
                : Auth(json::parse(serialized)) { }


            json Auth::to_json() const {

                return json{
                    { "type", enum_to_str(this->type)}, 
                    { "online", this->online},
                    { "user", this->user.to_json() }
                };
            }

        }

    }
}
