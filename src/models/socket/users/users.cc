#include "users.h"
#include "common/logger/logger.h"

/**
 * @brief Definizione modelli data Users (Json, enums): SIGNAL, Request, Response.
 * @file users.cc
 */

using namespace std;
using json = nlohmann::json;

namespace UsersSocket {

    SIGNAL str_to_enum(const std::string& users_action){
        if(users_action.compare("open") == 0)
            return SIGNAL::OPEN;
        else if(users_action.compare("close") == 0)
            return SIGNAL::CLOSE;
        else
            return SIGNAL::ALL;
    }

    std::string enum_to_str(const SIGNAL users_signal){

        switch(users_signal) {
            case SIGNAL::OPEN: 
                return "open";
            case SIGNAL::CLOSE:
                return "close";
            default:
                return "";
        }
    }

    Request::Request() {
        log_C(TAG::OBJ, "(Users)Request@JsonItem::Create", "");

        this->type = SIGNAL::ALL;
    }

    Request::Request(const json& j) {
        log_C(TAG::OBJ, "(Users)Request@JsonItem::Create", "...json...");

        this->type = str_to_enum(j.at("type").get<string>());
    }

    Request::Request(const std::string& serialized) 
        : Request(json::parse(serialized)) { }

    Request::~Request() {
        log_C(TAG::OBJ, "(Users)Request@JsonItem::Destroy", "");
    }

    json Request::to_json() const {
        return json {
            { "type", enum_to_str(this->type)}
        };
    }


    Response::Response() {
        log_C(TAG::OBJ, "(Users)Response@JsonItem::Create", "");

        this->type = SIGNAL::ALL;
        this->usersList = "[]";
    }

    Response::Response(const json& j) {
        log_C(TAG::OBJ, "(Users)Response@JsonItem::Create", "...json...");

        this->type = str_to_enum(j.at("type").get<string>());
        this->usersList = j.at("usersList").dump();
    }

    Response::Response(const std::string& serialized)
        : Response(json::parse(serialized)) { }

    Response::~Response() {
        log_C(TAG::OBJ, "(Users)Response@JsonItem::Destroy", "");
    }

    json Response::to_json() const {

        return json{
            { "type", enum_to_str(this->type)}, 
            { "usersList", json::parse(this->usersList)}
        };
    }

}