#include "chat.h"
#include "common/logger/logger.h"

/**
 * @brief Definizione modelli data Chat (Json, enums): SIGNAL, Request, Response.
 * @file chat.h
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

    Request::Request() {
        log_C(TAG::OBJ, "(Chat)Request@JsonItem::Create", "");

        this->type = SIGNAL::ALL;
    }

    Request::Request(const json& j) {
        log_C(TAG::OBJ, "(Chat)Request@JsonItem::Create", "...json...");

        this->type = str_to_enum(j.at("type").get<string>());
        this->text = j.at("text").get<string>();
    }

    Request::Request(const std::string& serialized) 
        : Request(json::parse(serialized)) { }

    Request::~Request() {
        log_C(TAG::OBJ, "(Chat)Request@JsonItem::Destroy", "");
    }

    json Request::to_json() const {
        return json {
            { "type", enum_to_str(this->type)},
            { "text", this->text }
        };
    }


    Response::Response() {
        log_C(TAG::OBJ, "(Chat)Response@JsonItem::Create", "");

        this->type = SIGNAL::ALL;
        this->isMe = false;
    }

    Response::Response(const json& j) {
        log_C(TAG::OBJ, "(Chat)Response@JsonItem::Create", "...json...");

        this->type = str_to_enum(j.at("type").get<string>());
        this->text = j.at("text").get<string>();
        this->ref  = j.at("ref").get<string>();
        this->time = j.at("time").get<string>();
        this->isMe = j.at("isMe").get<bool>();
        this->avatar = User(j.at("avatar"));
    }

    Response::Response(const std::string& serialized)
        : Response(json::parse(serialized)) { }

    Response::~Response() {
        log_C(TAG::OBJ, "(Chat)Response@JsonItem::Destroy", "");
    }

    json Response::to_json() const {

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