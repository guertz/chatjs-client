#include "json-item.h"
#include <string>

#include "common/logger/logger.h"

/**
 * @brief Definizione classe Json, base per oggetti di tipo Json 
 * @file json-item.cc
 */

using json = nlohmann::json;
using namespace std;

// Counter creazione oggetti temporeneo
static int obj_count = 0;

json JsonItem::to_json() const {
    return json::parse("{}");
}

string JsonItem::serialize() const {
    return this->to_json().dump();
}

JsonItem::JsonItem() {
    obj_count++;
    log_C(TAG::OBJ, "JsonItem::Create", "count: " + to_string(obj_count) );
}

JsonItem::~JsonItem() {
    obj_count--;
    log_C(TAG::OBJ, "JsonItem::Destroy", "count: " + to_string(obj_count) );
}