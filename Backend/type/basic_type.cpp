//
// Created by BALL on 2022/12/25.
//

#include "basic_type.h"

using namespace type;

UnitType::UnitType(BasicType b): basic(b), st(Structure::Normal) {}
UnitType::UnitType(BasicType b, Structure s): basic(b), st(s) {}
UnitType::UnitType(BasicType b, Structure s, StorageKind stok): basic(b), st(s), stk(stok) {}

std::string UnitType::to_string() {
    std::string content;
    switch (basic) {
        case Int16:
            content = "i16";
            break;
        case Int32:
            content = "i32";
            break;
        case Int64:
            content = "i64";
            break;
        case Float:
            content = "float";
            break;
        case Double:
            content = "double";
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
        case Object:
            content = "object";
            break;
    }
    return content;
}