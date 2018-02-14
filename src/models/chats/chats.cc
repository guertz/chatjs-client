#include "chats.h"
#include "common/logger/logger.h"

/**
 * @brief Definizione data models per messaggio/i (Json) 
 * @file chats.cc
 */

using namespace std;
using json = nlohmann::json;

Chat::Chat() {
    log_C(TAG::OBJ, "Chat@JsonItem::Create", "");
}

Chat::Chat(const nlohmann::json& j) {
    log_C(TAG::OBJ, "Chat@JsonItem::Create", "...json...");

    this->reference = j.at("reference").get<string>();
    this->destination = User(j.at("destination"));
    this->from = User(j.at("from"));
    this->creator = j.at("creator").get<string>();

    this->messages = MessagesWrapper::json_to_messages(j.at("messages"));

}

Chat::Chat(const std::string& serialized) 
    : Chat(json::parse(serialized)) { }

Chat::~Chat() {
    log_C(TAG::OBJ, "Chat@JsonItem::Destroy", "");
    this->messages.clear();
}

json Chat::to_json() const {

    return json{
        { "reference", this->reference },
        { "destination", this->destination.to_json() },
        { "from", this->from.to_json() },
        { "creator", this->creator },
        { "messages",  MessagesWrapper::messages_to_json(this->messages) }
    };

}

Chats ChatsWrapper::json_to_chats(const json& j) {
    Chats c_map;

    for (json::const_iterator it = j.cbegin(); it != j.cend(); ++it) {
        
        Chat c(it.value());

        c_map[c.reference] = c;
    }

    return c_map;
}

nlohmann::json ChatsWrapper::chats_to_json(const Chats& c) {
    json j_map = json::parse("[]");

    for (Chats::const_iterator it = c.cbegin(); it != c.cend(); ++it) {
        j_map.push_back(it->second.to_json());
    }

    return j_map;

}