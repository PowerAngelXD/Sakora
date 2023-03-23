//
// Created by BALL on 2023/1/26.
//

#include "type.h"

type::TSOption type::optBuilder(StructureKind st) {
    return TSOption {new StructureKind(st), nullptr};
}
type::TSOption type::optBuilder(UnitType ut) {
    return TSOption {nullptr, new UnitType(ut)};
}
type::TSOption type::optBuilder(BasicType bt) {
    return optBuilder(UnitType(bt));
}

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

std::string type::Type::to_string() {
    std::string content;
    if (this->isStructure()) {
        switch (*this->head.s_kind) {
            case Struct:
                break;
            case Array: {
                content += this->type_content[1].unit_type->to_string();
                content += "[]";
                break;
            }
            case VarArray: {
                content += "mutable ";
                content += this->type_content[1].unit_type->to_string();
                content += "[]";
                break;
            }
            case Impl:
                break;
            case Fn:
                break;
        }
    }
    else {
        content = this->head.unit_type->to_string();
    }

    return content;
}
