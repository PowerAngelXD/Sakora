//
// Created by BALL on 2022/12/25.
//

#include "basic_type.h"

using namespace type;

UnitType::UnitType(BasicType b): basic(b) {}
UnitType::UnitType(BasicType b, StorageKind stok): basic(b), stk(stok) {}

std::string UnitType::to_string() {
    std::string content;
    switch (basic) {
        case Integer:
            content = "int";
            break;
        case Decimal:
            content = "deci";
            break;
        case Boolean:
            content = "boolean";
            break;
        case String:
            content = "string";
            break;
        case Typeid:
            content = "typeid";
            break;
        case Flag:
            content = "flag";
            break;
        case Void:
            content = "void";
            break;
    }
    return content;
}