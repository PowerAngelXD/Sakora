//
// Created by BALL on 2023/1/26.
//

#include "type.h"

type::Type::Type(UnitType unit_type) {
    type_content.push_back({nullptr, new UnitType(unit_type)});
    head = type_content[0];
}
type::Type::Type(std::initializer_list<TSOption> TS_list) {
    for (auto element: TS_list) {
        type_content.push_back(element);
    }
    head = type_content[0];
}

bool type::Type::isStructure() const {
    return head.s_kind != nullptr;
}

bool type::Type::operator== (Type t) {
    for(size_t i = 0; i < this->type_content.size(); i ++) {
        if (!(this->type_content[i].unit_type == t.type_content[i].unit_type &&
            this->type_content[i].s_kind == t.type_content[i].s_kind))
            return false;
    }
    return true;
}
bool type::Type::operator!= (Type t) {
    return !this->operator==(t);
}