#include "message.h"

using namespace std;
using json = nlohmann::json;

namespace States {
    namespace ChatState {

        Message::Message() {
            this->isMe = false;
        }

        Message::Message(const json& j) {
            this->text = j.at("text").get<string>();
            this->isMe = j.at("isMe").get<bool>();
            this->avatar = User(j.at("avatar"));
            this->time = j.at("time").get<string>();
        }

        Message::Message(const std::string& serialized)
             : Message(json::parse(serialized)) { }
        
        json Message::to_json() const {
            return json{
                { "text", this->text },
                { "isMe", this->isMe },
                { "avatar", this->avatar.to_json() },
                { "time", this->time }
            };
        }

        void MessagesWrapper::json_to_messages(const json& j, Messages& m_vect) {
            for (json::const_reverse_iterator it = j.crbegin(); it != j.crend(); ++it) {
                
                Message m(it.value());

                m_vect.push_back(m);
            }
        }

        void MessagesWrapper::messages_to_json(const Messages& m, json& j_vect) {
            j_vect = json::parse("[]");

            for (Messages::const_reverse_iterator it = m.crbegin(); it != m.crend(); ++it) {
                j_vect.push_back((*it).to_json());
            }

        }
        

    }
}
