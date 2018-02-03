#include "request.h"

using json = nlohmann::json;
using namespace std;

namespace ws {

    BaseRequest::BaseRequest() {
        this->AUTH = "";
        this->content = "";
    }
    
    BaseRequest::BaseRequest(const json& j) {
        this->AUTH = j.at("AUTH").get<string>();
        this->content = j.at("content").dump();
    }

    BaseRequest::BaseRequest(const std::string& serialized) 
            : BaseRequest(json::parse(serialized)) { }

    json BaseRequest::to_json() const {
        return json{ 
            { "AUTH", this->AUTH },
            { "content", json::parse(this->content) }
        };
    }

}