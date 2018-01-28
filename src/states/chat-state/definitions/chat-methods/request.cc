#include "request.h"

using json = nlohmann::json;
using namespace std;

namespace States {

    namespace ChatState {

        namespace ChatMethods {

            namespace Request {

                Chat::Chat() {
                    this->type = TYPE::ALL;
                }

                Chat::Chat(const json& j) {
                    this->type = str_to_enum(j.at("type").get<string>());
                    this->text = j.at("text").get<string>();
                }

                Chat::Chat(const string& serialized) : Chat(json::parse(serialized)) { }

                json Chat::to_json() const {
                    return json{
                        { "type", enum_to_str(this->type)},
                        { "text", this->text }
                    };
                }
            }
            
        }
    }
}