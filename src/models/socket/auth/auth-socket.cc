#include "auth-socket.h"
#include "common/logger/logger.h"

/**
 * @brief Definizione modelli data AuthSocket (Json, enums): AuthSocket::SIGNAL, AuthSocket::AuthRequest, AuthSocket::AuthResponse.
 * @file auth-socket.cc
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

    AuthRequest::AuthRequest() {
        log_details(TAG::OBJ, "AuthRequest@JsonItem::Create", "");

        this->type = SIGNAL::ALL;
        this->user = "";
    }

    AuthRequest::AuthRequest(const nlohmann::json& j) {
        log_details(TAG::OBJ, "AuthRequest@JsonItem::Create", "...json...");

        this->type = str_to_enum(j.at("type").get<string>());
        this->user = j.at("user").get<string>();
    }

    AuthRequest::AuthRequest(const std::string& serialized) 
        : AuthRequest(json::parse(serialized)) { }

    AuthRequest::~AuthRequest() {
        log_details(TAG::OBJ, "AuthRequest@JsonItem::Destroy", "");
    }

    nlohmann::json AuthRequest::to_json() const {
        return json{
            { "type", enum_to_str(this->type)}, 
            { "user", this->user }
        };
    }

    AuthResponse::AuthResponse() {
        log_details(TAG::OBJ, "AuthResponse@JsonItem::Create", "");

        this->type = SIGNAL::ALL;
        this->online = false;
    }

    AuthResponse::AuthResponse(const nlohmann::json& j) {
        log_details(TAG::OBJ, "AuthResponse@JsonItem::Create", "...json...");

        this->type = str_to_enum(j.at("type").get<string>());
        this->online = j.at("online").get<bool>();
        this->user   = User(j.at("user"));
    }

    AuthResponse::AuthResponse(const std::string& serialized)
        : AuthResponse(json::parse(serialized)) { }

    AuthResponse::~AuthResponse() {
        log_details(TAG::OBJ, "AuthResponse@JsonItem::Destroy", "");
    }


    nlohmann::json AuthResponse::to_json() const {

        return json{
            { "type", enum_to_str(this->type)}, 
            { "online", this->online},
            { "user", this->user.to_json() }
        };
    }  

}