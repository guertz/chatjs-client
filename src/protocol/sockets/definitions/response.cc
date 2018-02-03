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

    BaseResponse::BaseResponse(const nlohmann::json& j) {
        this->ok = j.at("ok").get<bool>();
        this->status = j.at("status").get<int>();
        this->error = j.at("error").get<string>();
        this->content = j.at("content").dump();
    }

    BaseResponse::BaseResponse(const std::string& serialized) 
        : BaseResponse(json::parse(serialized)) { }

    json BaseResponse::to_json() const {
        return json { 
            { "ok", this->ok },
            { "status", this->status }, 
            { "error", this->error},
            { "content", json::parse(this->content)}
        };
    }

}