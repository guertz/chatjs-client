#include "chats-socket.h"
#include "common/logger/logger.h"

/**
 * @brief Definizione modelli data ChatsSocket (Json, enums): ChatsSocket::SIGNAL, ChatsSocket::ChatsRequest, ChatsSocket::ChatsResponse.
 * @file chats-socket.h
 */

using namespace std;
using json = nlohmann::json;

namespace ChatsSocket {

    SIGNAL str_to_enum(const std::string& chats_action){
        if(chats_action.compare("create") == 0)
            return SIGNAL::CREATE;
        else if(chats_action.compare("connect") == 0)
            return SIGNAL::CONNECT;
        else
            return SIGNAL::ALL;
    }

    std::string enum_to_str(const SIGNAL chats_signal){

        switch(chats_signal) {
            case SIGNAL::CREATE: 
                return "create";
            case SIGNAL::CONNECT:
                return "connect";
            default:
                return "";
        }
    }

    ChatsRequest::ChatsRequest() {
        log_C(TAG::OBJ, "ChatsRequest@JsonItem::Create", "");

        this->type = SIGNAL::ALL;
    }

    ChatsRequest::ChatsRequest(const nlohmann::json& j) {
        log_C(TAG::OBJ, "ChatsRequest@JsonItem::Create", "...json...");

        this->type = str_to_enum(j.at("type").get<string>());
        this->destination = j.at("destination").get<string>();
    }

    ChatsRequest::ChatsRequest(const std::string& serialized) 
        : ChatsRequest(json::parse(serialized)) { }

    ChatsRequest::~ChatsRequest() {
        log_C(TAG::OBJ, "ChatsRequest@JsonItem::Destroy", "");
    }

    nlohmann::json ChatsRequest::to_json() const {
        return json {
            { "type", enum_to_str(this->type)},
            { "destination", this->destination }
        };
    }


    ChatsResponse::ChatsResponse() {
        log_C(TAG::OBJ, "ChatsResponse@JsonItem::Create", "");

        this->type = SIGNAL::ALL;
    }

    ChatsResponse::ChatsResponse(const nlohmann::json& j) {
        log_C(TAG::OBJ, "ChatsResponse@JsonItem::Create", "...json...");

        this->type = str_to_enum(j.at("type").get<string>());
        this->reference = j.at("reference").get<string>();
        this->destination = User(j.at("destination"));
        this->from = User(j.at("from"));
        this->creator = j.at("creator").get<string>();
    }

    ChatsResponse::ChatsResponse(const std::string& serialized)
        : ChatsResponse(json::parse(serialized)) { }

    ChatsResponse::~ChatsResponse() {
        log_C(TAG::OBJ, "ChatsResponse@JsonItem::Destroy", "");
    }

    nlohmann::json ChatsResponse::to_json() const {

        return json{
            { "type", enum_to_str(this->type)},
            { "reference", this->reference },
            { "destination", this->destination.to_json() },
            { "from", this->from.to_json() },
            { "creator", this->creator }
        };
    }

}