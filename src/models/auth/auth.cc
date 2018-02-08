#include "auth.h"
#include "common/logger/logger.h"

/**
 * @brief Definizione modelli data Auth (Json, enums): AUTHSIGNAL, AuthRequest, AuthResponse.
 * @file auth.cc
 */


using namespace std;
using json = nlohmann::json;

AUTHSIGNAL str_to_enum(const std::string& AUTH_ACTION){
    if(AUTH_ACTION.compare("login") == 0)
        return AUTHSIGNAL::LOGIN;
    else if(AUTH_ACTION.compare("logout") == 0)
        return AUTHSIGNAL::LOGOUT;
    else
        return AUTHSIGNAL::ALL;
}

std::string enum_to_str(const AUTHSIGNAL AUTH_ACTION){

    switch(AUTH_ACTION) {
        case AUTHSIGNAL::LOGIN: 
            return "login";
        case AUTHSIGNAL::LOGOUT:
            return "logout";
        default:
            return "";
    }
}

AuthRequest::AuthRequest() {
    log_details("AuthRequest@JsonItem", "Created");

    this->type = AUTHSIGNAL::Log;
    this->user = "";
}

AuthRequest::AuthRequest(const json& j) {
    log_details("AuthRequest@JsonItem", "Created from json");

    this->type = str_to_enum(j.at("type").get<string>());
    this->user = j.at("user").get<string>();
}

AuthRequest::AuthRequest(const std::string& serialized) 
    : AuthRequest(json::parse(serialized)) { }

AuthRequest::~AuthRequest() {
    log_details("AuthRequest@JsonItem", "Destroying");
}

json AuthRequest::to_json() const {
    return json{
        { "type", enum_to_str(this->type)}, 
        { "user", this->user }
    };
}

AuthResponse::AuthResponse() {
    log_details("AuthResponse@JsonItem", "Created");

    this->type = AUTHSIGNAL::LOGOUT;
    this->online = false;
    // this->user // default constructor
}

AuthResponse::AuthResponse(const json& j) {
    log_details("AuthResponse@JsonItem", "Created from json");

    this->type = str_to_enum(j.at("type").get<string>());
    this->online = j.at("online").get<bool>();
    this->user   = User(j.at("user"));
}

AuthResponse::AuthResponse(const std::string& serialized)
    : AuthResponse(json::parse(serialized)) { }

AuthResponse::~AuthResponse() {
    log_details("AuthResponse@JsonItem", "Destroying");
}


json AuthResponse::to_json() const {

    return json{
        { "type", enum_to_str(this->type)}, 
        { "online", this->online},
        { "user", this->user.to_json() }
    };
}
