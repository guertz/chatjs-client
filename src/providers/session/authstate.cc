#include <iostream>
#include "authstate.h"
#include "providers/sockets/wscustom.h"
#include "common/helpers/helpers.h"
#include "user.h"
#include <json.hpp>

using json = nlohmann::json;
using namespace ws;
using namespace std;
using namespace Helpers;

static Socket *authSocket = 0; // remember to clean up
static bool pending       = false;
static bool loggedIn   = false;
static AuthState::auth_component_list subscribed;
static char* cached = 0; // remember to clean up

const char* AuthState::getAuthStatus(){

    //throw exception
    return cached ? safestr::duplicate(cached) : 0;
}

// Interface optimization (include all function but static/inline)
void notify(const char* args){
    
    safeptr::free_block(cached);
    cached = safestr::duplicate(args);

    for (const auto& item : subscribed) {
        cout<<"Notify->"<<item.first<<endl;
        // all components need to delete
        (*item.second)(safestr::duplicate(args));
    }

    safeptr::free_block(args);

}

void AuthState::Register(string abc, void (*fn)(const char* arg)){
    subscribed[abc] = fn;
}


void AuthState::logout(){
    json jExtern;
    jExtern["action"] = AuthState::AUTHSIGNAL::LOGOUT;
    jExtern["failure"] = false;

    notify(safestr::duplicate(jExtern.dump().c_str()));

    authSocket->stop();
    delete authSocket;

    authSocket = new Socket("users",false);

}

void AuthState::Bootstrap() {

    authSocket = new Socket("users",false);
}


//detect login, logout..
// throw catch system
// can be done by socket primary handler
// handle interruption socket
// TODO delete args
void receiveLoginAction(const char* args){

    cout<<"########## AUTHSTATE CHANGES #######"<<endl;
    
    if(strlen(args) > 0 && args[0] == '{'){
        json jIntern = json::parse(args);
        
        if(!jIntern["error"].get<int>()){
            AuthState::AuthUser profile;
                profile._id = jIntern["attributes"]["_id"].get<std::string>();
                profile.online = true;
                profile.name = jIntern["attributes"]["name"].get<std::string>();
                profile.image = jIntern["attributes"]["image"].get<std::string>();       


            json jExtern;
                jExtern["action"] = AuthState::AUTHSIGNAL::LOGIN;
                jExtern["failure"] = false;
                jExtern["name"] = profile.name;
                jExtern["_id"] = profile._id;
                jExtern["image"] = profile.image;
                jExtern["online"] = true;

            notify(safestr::duplicate(jExtern.dump().c_str()));
            

        }else{
            json jError;
                jError["action"]  = AuthState::AUTHSIGNAL::LOGIN;
                jError["failure"] = true;
            
            notify(safestr::duplicate(jError.dump().c_str()));

            authSocket->stop();
            delete authSocket;
        
            authSocket = new Socket("users",false);
        } 
    }

    pending = false;

}

void AuthState::Login(const char* args){
    if(!pending && !loggedIn){
        pending = true;
        
        json jdump = json::parse(args);

        json jUser = R"(
            {
                "type": "login",
                "content": {
                    "id": "fakecontent"
                }
            }
        )"_json;

        jUser["content"]["id"] = jdump["params"]["userid"];
        authSocket->write(jUser.dump(), receiveLoginAction);
    }

}