#include "auth.h"
#include "common/logger/logger.h"

/**
 * @brief Definizione modelli data Auth (Json, enums): SIGNAL, Request, Response.
 * @file auth.cc
 */

using namespace std;
using json = nlohmann::json;

namespace AuthSocket {
    
    SIGNAL str_to_enum(const std::string& auth_action){
        if(auth_action.compare("login") == 0)
            return SIGNAL::LOGIN;
        else if(auth_action.compare("logout") == 0)
            return SIGNAL::LOGOUT;
        else
            return SIGNAL::ALL;
    }

    std::string enum_to_str(const SIGNAL auth_signal){

        switch(auth_signal) {
            case SIGNAL::LOGIN: 
                return "login";
            case SIGNAL::LOGOUT:
                return "logout";
            default:
                return "";
        }
    }

    Request::Request() {
        log_C(TAG::OBJ, "(Auth)Request@JsonItem::Create", "");

        this->type = SIGNAL::ALL;
        this->user = "";
    }

    Request::Request(const json& j) {
        log_C(TAG::OBJ, "(Auth)Request@JsonItem::Create", "...json...");

        this->type = str_to_enum(j.at("type").get<string>());
        this->user = j.at("user").get<string>();
    }

    Request::Request(const std::string& serialized) 
        : Request(json::parse(serialized)) { }

    Request::~Request() {
        log_C(TAG::OBJ, "(Auth)Request@JsonItem::Destroy", "");
    }

    json Request::to_json() const {
        return json{
            { "type", enum_to_str(this->type)}, 
            { "user", this->user }
        };
    }

    Response::Response() {
        log_C(TAG::OBJ, "(Auth)Response@JsonItem::Create", "");

        this->type = SIGNAL::ALL;
        this->online = false;
    }

    Response::Response(const json& j) {
        log_C(TAG::OBJ, "(Auth)Response@JsonItem::Create", "...json...");

        this->type = str_to_enum(j.at("type").get<string>());
        this->online = j.at("online").get<bool>();
        this->user   = User(j.at("user"));
    }

    Response::Response(const std::string& serialized)
        : Response(json::parse(serialized)) { }

    Response::~Response() {
        log_C(TAG::OBJ, "Auth(Response)@JsonItem::Destroy", "");
    }


    json Response::to_json() const {

        return json{
            { "type", enum_to_str(this->type)}, 
            { "online", this->online},
            { "user", this->user.to_json() }
        };
    }  

}