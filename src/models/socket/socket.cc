#include "socket.h"
#include "common/logger/logger.h"

using json = nlohmann::json;
using namespace std;

/**
 * @brief Definizione modelli Socket (Json): BaseRequest, BaseResponse.
 * @file socket.cc
 */

namespace ws {

    BaseRequest::BaseRequest() {
        log_pedantic("BaseRequest@JsonItem", "Created");

        // this->AUTH = "";
        // this->content = "";
    }
    
    BaseRequest::BaseRequest(const json& j) {
        log_pedantic("BaseRequest@JsonItem", "Created from json");

        this->AUTH = j.at("AUTH").get<string>();
        this->content = j.at("content").dump();
    }

    BaseRequest::BaseRequest(const std::string& serialized) 
            : BaseRequest(json::parse(serialized)) { }

    BaseRequest::~BaseRequest() {
        log_pedantic("BaseRequest@JsonItem", "Destroying");
    }

    json BaseRequest::to_json() const {
        return json{ 
            { "AUTH", this->AUTH },
            { "content", json::parse(this->content) }
        };
    }

    BaseResponse::BaseResponse() {
        log_pedantic("BaseResponse@JsonItem", "Created");

        this->ok      = false;
        this->status  = 0;
        // this->content = "";
        // this->error   = "";
    }

    BaseResponse::BaseResponse(const nlohmann::json& j) {
        log_pedantic("BaseResponse@JsonItem", "Created from json");

        this->ok = j.at("ok").get<bool>();
        this->status = j.at("status").get<int>();
        this->error = j.at("error").get<string>();
        this->content = j.at("content").dump();
    }

    BaseResponse::BaseResponse(const std::string& serialized) 
        : BaseResponse(json::parse(serialized)) { }

    BaseResponse::~BaseResponse() {
        log_pedantic("BaseResponse@JsonItem", "Destroying");
    }

    json BaseResponse::to_json() const {
        return json { 
            { "ok", this->ok },
            { "status", this->status }, 
            { "error", this->error},
            { "content", json::parse(this->content)}
        };
    }

}