#include "message.h"
#include "common/logger/logger.h"

/**
 * @brief Definizione data models per messaggio/i (Json) 
 * @file message.cc
 */

using namespace std;
using json = nlohmann::json;

Message::Message() {
    log_details(TAG::OBJ, "Message@JsonItem::Create", "");

    this->isMe = false;
}

Message::Message(const nlohmann::json& j) {
    log_details(TAG::OBJ, "Message@JsonItem::Create", "...json...");

    this->text = j.at("text").get<string>();
    this->isMe = j.at("isMe").get<bool>();
    this->avatar = User(j.at("avatar"));
    this->time = j.at("time").get<string>();
}

Message::Message(const std::string& serialized)
        : Message(json::parse(serialized)) { }

Message::~Message() {
    log_details(TAG::OBJ, "Message@JsonItem::Destroy", "");
}

nlohmann::json Message::to_json() const {
    return json{
        { "text", this->text },
        { "isMe", this->isMe },
        { "avatar", this->avatar.to_json() },
        { "time", this->time }
    };
}

Messages MessagesWrapper::json_to_messages(const nlohmann::json& j) {
    Messages m_vect;

    for (json::const_reverse_iterator it = j.crbegin(); it != j.crend(); ++it) {
        
        Message m(it.value());

        m_vect.push_back(m);
    }

    return m_vect;
}

nlohmann::json MessagesWrapper::messages_to_json(const Messages& m) {
    json j_vect = json::parse("[]");

    for (Messages::const_reverse_iterator it = m.crbegin(); it != m.crend(); ++it) {
        j_vect.push_back((*it).to_json());
    }

    return j_vect;

}

