#include "response.h"

using json = nlohmann::json;
using namespace std;

namespace ws {

    BaseResponse::BaseResponse() {
        this->ok      = false;
        this->status  = 0;
        this->content = "";
        this->error   = "";
    }

    BaseResponse::BaseResponse(const nlohmann::json& j) : BaseResponse() {
        this->from_json(j);
    }

    BaseResponse::BaseResponse(const std::string& serialized) : BaseResponse() {
        this->from_json(json::parse(serialized));
    }

    void BaseResponse::from_json(const nlohmann::json& j) {
        this->ok = j.at("ok").get<bool>();
        this->status = j.at("status").get<int>();
        this->error = j.at("error").get<string>();
        this->content = j.at("content").dump();
    }

    json BaseResponse::to_json() {
        return json { 
            { "ok", this->ok },
            { "status", this->status }, 
            { "error", this->error},
            { "content", json::parse(this->content)}
        };
    }

    string BaseResponse::serialize() {
        return this->to_json().dump();
    }
}