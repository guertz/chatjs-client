#include "user.h"

using json = nlohmann::json;
using namespace std;

namespace States {
    namespace AuthState {

        User::User(){
            this->name  = "";
            this->_id   = "";
            this->image = "";
        }

        User::User(const json& j) : User() {
            this->from_json(j);
        }

        User::User(const string& serialized) : User() {
            this->from_json(json::parse(serialized));
        }

        void User::from_json(const json& j) {
            if(j.is_object()) {
                this->name = j.at("name").get<string>();
                this->image = j.at("image").get<string>();
                this->_id = j.at("_id").get<string>();
            }
        }
        
        json User::to_json() {
            return json{
                { "name", this->name}, 
                { "image", this->image}, 
                { "_id", this->_id}
            };
        }

        string User::serialize() {
            return this->to_json().dump();
        }
        
        bool User::is_valid() {
            return this->_id.size() > 0;
        }
        
    }
}