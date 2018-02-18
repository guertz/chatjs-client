#include "users-socket.h"
#include "common/logger/logger.h"

/**
 * @brief Definizione modelli data UsersSocket (Json, enums): UsersSocket::SIGNAL, UsersSocket::UsersRequest, UsersSocket::UsersResponse.
 * @file users-socket.cc
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

    UsersRequest::UsersRequest() {
        log_details(TAG::OBJ, "UsersRequest@JsonItem::Create", "");

        this->type = SIGNAL::ALL;
    }

    UsersRequest::UsersRequest(const nlohmann::json& j) {
        log_details(TAG::OBJ, "UsersRequest@JsonItem::Create", "...json...");

        this->type = str_to_enum(j.at("type").get<string>());
    }

    UsersRequest::UsersRequest(const std::string& serialized) 
        : UsersRequest(json::parse(serialized)) { }

    UsersRequest::~UsersRequest() {
        log_details(TAG::OBJ, "UsersRequest@JsonItem::Destroy", "");
    }

    json UsersRequest::to_json() const {
        return json {
            { "type", enum_to_str(this->type)}
        };
    }


    UsersResponse::UsersResponse() {
        log_details(TAG::OBJ, "UsersResponse@JsonItem::Create", "");

        this->type = SIGNAL::ALL;
        this->usersList = "[]";
    }

    UsersResponse::UsersResponse(const nlohmann::json& j) {
        log_details(TAG::OBJ, "UsersResponse@JsonItem::Create", "...json...");

        this->type = str_to_enum(j.at("type").get<string>());
        this->usersList = j.at("usersList").dump();
    }

    UsersResponse::UsersResponse(const std::string& serialized)
        : UsersResponse(json::parse(serialized)) { }

    UsersResponse::~UsersResponse() {
        log_details(TAG::OBJ, "UsersResponse@JsonItem::Destroy", "");
    }

    json UsersResponse::to_json() const {

        return json{
            { "type", enum_to_str(this->type)}, 
            { "usersList", json::parse(this->usersList)}
        };
    }

}