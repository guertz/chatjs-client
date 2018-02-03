#include "request.h"

using json = nlohmann::json;
using namespace std;

namespace States {

    namespace ChatState {

        namespace ChatsMethods {

            namespace Request {
                
                Chats::Chats() { 
                    this->type = TYPE::ALL;
                }

                Chats::Chats(const json& j) {
                    this->type = str_to_enum(j.at("type").get<string>());
                    this->destination = j.at("destination").get<string>();
                }
                
                Chats::Chats(const std::string& serialized) 
                    : Chats(json::parse(serialized)) { }

                json Chats::to_json() const {
                    return json{
                        { "type", enum_to_str(this->type)},
                        { "destination", this->destination }
                    };
                }
            }
            
        }
    }
}