#include "response.h"

using json = nlohmann::json;
using namespace std;

namespace States {

    namespace ChatState {

        namespace ChatsMethods {

            namespace Response {
                
                Chats::Chats() {
                    this->type = TYPE::ALL;
                }

                Chats::Chats(const json& j) {
                    this->type = str_to_enum(j.at("type").get<string>());
                    this->reference = j.at("reference").get<string>();
                    this->destination = User(j.at("destination"));
                    this->from = User(j.at("from"));
                    this->creator = j.at("creator").get<string>();
                }

                Chats::Chats(const string& serialized) : Chats(json::parse(serialized)) { }

                json Chats::to_json() const {
                    return json{
                        { "type", enum_to_str(this->type)},
                        { "reference", this->reference },
                        { "destination", this->destination.to_json() },
                        { "from", this->from.to_json() },
                        { "creator", this->creator }
                    };
                }  

            }
        }
        
    }
}