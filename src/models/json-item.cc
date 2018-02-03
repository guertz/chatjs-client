#include "json-item.h"

using json = nlohmann::json;
using namespace std;

json JsonItem::to_json() const {
    return json::parse("{}");
}

string JsonItem::serialize() const {
    return this->to_json().dump();
}