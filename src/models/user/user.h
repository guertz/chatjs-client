#ifndef MODELS_USER_USER_H
#define MODELS_USER_USER_H

#include <iostream>
#include <json.hpp>
#include "models/json-item.h"

class User : public JsonItem {

    public:
        std::string name;
        std::string image;
        std::string _id;

        User();
        User(const nlohmann::json& j);
        User(const std::string& serialized);

        nlohmann::json to_json() const ;
        
        bool is_valid() const;
};

#endif