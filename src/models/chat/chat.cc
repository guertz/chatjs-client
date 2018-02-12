#include "chat.h"

using namespace std;
using json = nlohmann::json;

Chat::Chat() {

}

Chat::Chat(const nlohmann::json& j) {
    this->reference = j.at("reference").get<string>();
    this->destination = User(j.at("destination"));
    this->from = User(j.at("from"));
    this->creator = j.at("creator").get<string>();

    MessagesWrapper::json_to_messages(j.at("messages"), this->messages);

}

Chat::Chat(const std::string& serialized) 
    : Chat(json::parse(serialized)) { }

json Chat::to_json() const {

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

Chat::~Chat() {
    this->messages.clear();
}

void ChatsWrapper::json_to_chats(const json& j, Chats& c_map) {
    for (json::const_iterator it = j.cbegin(); it != j.cend(); ++it) {
        
        Chat c(it.value());

        c_map[c.reference] = c;
    }
}

void ChatsWrapper::chats_to_json(const Chats& c, json& j_map) {
    j_map = json::parse("[]");

    for (Chats::const_iterator it = c.cbegin(); it != c.cend(); ++it) {
        j_map.push_back(it->second.to_json());
    }

}