#include "request.h"

using json = nlohmann::json;
using namespace std;

namespace ws {

    BaseRequest::BaseRequest() {
        this->AUTH = "";
        this->content = "";
    }
    
    BaseRequest::BaseRequest(const json& j) : BaseRequest() {
        this->from_json(j);
    }

    BaseRequest::BaseRequest(const string& serialized) : BaseRequest() {
        this->from_json(json::parse(serialized));
    }

    void BaseRequest::from_json(const json& j){
        this->AUTH = j.at("AUTH").get<string>();
        this->content = j.at("content").dump();
    }

    json BaseRequest::to_json(){
        return json{ 
            { "AUTH", this->AUTH },
            { "content", json::parse(this->content) }
        };
    }

    string BaseRequest::serialize() {
        return this->to_json().dump();
    }
}