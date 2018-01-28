#ifndef MODELS_JSONITEM_H
#define MODELS_JSONITEM_H

#include <iostream>
#include <json.hpp>
            
class JsonItem {

    public: 
        virtual nlohmann::json to_json() const;
        std::string serialize() const;
        

};


#endif