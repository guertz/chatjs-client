#include "response.h"
#include "common/logger/logger.h"

using json = nlohmann::json;
using namespace std;

namespace States {

    namespace ChatState {

        namespace ChatMethods {

            namespace Response {
                
                Chat::Chat() {
                    this->type = TYPE::ALL;
                    this->isMe = false;
                }

                Chat::Chat(const json& j) {
                    this->type = str_to_enum(j.at("type").get<string>());
                    this->text = j.at("text").get<string>();
                    this->ref  = j.at("ref").get<string>();
                    this->time = j.at("time").get<string>();
                    this->isMe = j.at("isMe").get<bool>();
                    this->avatar = User(j.at("avatar"));
                }

                Chat::Chat(const string& serialized) : Chat(json::parse(serialized)) { }

                json Chat::to_json() const {
                    return json{
                        { "type", enum_to_str(this->type)},
                        { "text", this->text },
                        { "ref", this->ref},
                        { "time", this->time },
                        { "isMe", this->isMe },
                        { "avatar", this->avatar.to_json() }
                    };
                }

            }
        }
        
    }
}