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

            Auth::Auth(const json& j) : Auth() {
                this->from_json(j);
            }

            Auth::Auth(const string& serialized) : Auth() {
                json j = json::parse(serialized);
                this->from_json(j);
            }

            void Auth::from_json(const json& j) {
                this->type = str_to_enum(j.at("type").get<string>());
                this->online = j.at("online").get<bool>();
                this->user   = User(j.at("user"));
            }

            json Auth::to_json() {

                return json{
                    { "type", enum_to_str(this->type)}, 
                    { "online", this->online},
                    { "user", this->user.to_json() }
                };
            }

            string Auth::serialize() {
                return this->to_json().dump();
            }

        }

    }
}
