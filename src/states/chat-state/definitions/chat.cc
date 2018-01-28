#include "chat.h"

using namespace std;
using json = nlohmann::json;

namespace States {
    namespace ChatState {

        Chat::Chat() {
        
        }

        Chat::Chat(const nlohmann::json& j) {
            this->reference = j.at("reference").get<string>();
            this->destination = User(j.at("destination"));
            this->from = User(j.at("from"));
            this->creator = j.at("creator").get<string>();
            MessagesWrapper::json_to_messages(j.at("messages"), this->messages);
        }

        Chat::Chat(const std::string& serialized) : Chat(json::parse(serialized)) { }
        
        nlohmann::json Chat::to_json() const {

            // with a function, use return type
            //  or in static i can create objets?
            json j_vect;
            MessagesWrapper::messages_to_json(this->messages, j_vect);

            return json{
                { "reference", this->reference },
                { "destination", this->destination.to_json() },
                { "from", this->from.to_json() },
                { "creator", this->creator },
                { "messages", j_vect }
            };

        }

    }    
}