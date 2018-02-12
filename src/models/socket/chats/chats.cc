#include "chats.h"
#include "common/logger/logger.h"

/**
 * @brief Definizione modelli data Chats (Json, enums): SIGNAL, Request, Response.
 * @file chats.h
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

    Request::Request() {
        log_C(TAG::OBJ, "(Chats)Request@JsonItem::Create", "");

        this->type = SIGNAL::ALL;
    }

    Request::Request(const json& j) {
        log_C(TAG::OBJ, "(Chats)Request@JsonItem::Create", "...json...");

        this->type = str_to_enum(j.at("type").get<string>());
        this->destination = j.at("destination").get<string>();
    }

    Request::Request(const std::string& serialized) 
        : Request(json::parse(serialized)) { }

    Request::~Request() {
        log_C(TAG::OBJ, "(Chats)Request@JsonItem::Destroy", "");
    }

    json Request::to_json() const {
        return json {
            { "type", enum_to_str(this->type)},
            { "destination", this->destination }
        };
    }


    Response::Response() {
        log_C(TAG::OBJ, "(Chats)Response@JsonItem::Create", "");

        this->type = SIGNAL::ALL;
    }

    Response::Response(const json& j) {
        log_C(TAG::OBJ, "(Chats)Response@JsonItem::Create", "...json...");

        this->type = str_to_enum(j.at("type").get<string>());
        this->reference = j.at("reference").get<string>();
        this->destination = User(j.at("destination"));
        this->from = User(j.at("from"));
        this->creator = j.at("creator").get<string>();
    }

    Response::Response(const std::string& serialized)
        : Response(json::parse(serialized)) { }

    Response::~Response() {
        log_C(TAG::OBJ, "(Chats)Response@JsonItem::Destroy", "");
    }

    json Response::to_json() const {

        return json{
            { "type", enum_to_str(this->type)},
            { "reference", this->reference },
            { "destination", this->destination.to_json() },
            { "from", this->from.to_json() },
            { "creator", this->creator }
        };
    }

}