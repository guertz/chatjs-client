#include "json-item.h"
#include <string>

#include "common/logger/logger.h"

/**
 * @brief Definizione classe Json, base per oggetti di tipo Json 
 * @file json-item.cc
 */

using json = nlohmann::json;
using namespace std;


nlohmann::json JsonItem::to_json() const {
    return json::parse("{}");
}

std::string JsonItem::serialize() const {
    return this->to_json().dump();
}