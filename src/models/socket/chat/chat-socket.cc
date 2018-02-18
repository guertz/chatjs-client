#include "chat-socket.h"
#include "common/logger/logger.h"

/**
 * @brief Definizione modelli data ChatSocket (Json, enums): ChatSocket::SIGNAL, ChatSocket::ChatRequest, ChatSocket::ChatResponse.
 * @file chat-socket.h
 */

using namespace std;
using json = nlohmann::json;

namespace ChatSocket {

    SIGNAL str_to_enum(const std::string& chat_action){

        if(chat_action.compare("join") == 0)
            return SIGNAL::JOIN;
        else if(chat_action.compare("send") == 0)
            return SIGNAL::SEND;

        return SIGNAL::ALL;
    }

    std::string enum_to_str(const SIGNAL chat_signal){

        switch(chat_signal) {
            case SIGNAL::JOIN: 
                return "join";

            case SIGNAL::SEND:
                return "send";

            default:
                return "";
        }
    }

    ChatRequest::ChatRequest() {
        log_details(TAG::OBJ, "ChatRequest@JsonItem::Create", "");

        this->type = SIGNAL::ALL;
    }

    ChatRequest::ChatRequest(const  nlohmann::json& j) {
        log_details(TAG::OBJ, "ChatRequest@JsonItem::Create", "...json...");

        this->type = str_to_enum(j.at("type").get<string>());
        this->text = j.at("text").get<string>();
    }

    ChatRequest::ChatRequest(const std::string& serialized) 
        : ChatRequest(json::parse(serialized)) { }

    ChatRequest::~ChatRequest() {
        log_details(TAG::OBJ, "ChatRequest@JsonItem::Destroy", "");
    }

    nlohmann::json ChatRequest::to_json() const {
        return json {
            { "type", enum_to_str(this->type)},
            { "text", this->text }
        };
    }


    ChatResponse::ChatResponse() {
        log_details(TAG::OBJ, "ChatResponse@JsonItem::Create", "");

        this->type = SIGNAL::ALL;
        this->isMe = false;
    }

    ChatResponse::ChatResponse(const nlohmann::json& j) {
        log_details(TAG::OBJ, "ChatResponse@JsonItem::Create", "...json...");

        this->type = str_to_enum(j.at("type").get<string>());
        this->text = j.at("text").get<string>();
        this->ref  = j.at("ref").get<string>();
        this->time = j.at("time").get<string>();
        this->isMe = j.at("isMe").get<bool>();
        this->avatar = User(j.at("avatar"));
    }

    ChatResponse::ChatResponse(const std::string& serialized)
        : ChatResponse(json::parse(serialized)) { }

    ChatResponse::~ChatResponse() {
        log_details(TAG::OBJ, "ChatResponse@JsonItem::Destroy", "");
    }

    nlohmann::json ChatResponse::to_json() const {

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