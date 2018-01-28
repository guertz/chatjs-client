#include "json-item.h"

using json = nlohmann::json;
using namespace std;

json JsonItem::to_json() const {
    json x = json::parse("{}");
    return x ;
}

string JsonItem::serialize() const {
    return this->to_json().dump();
}