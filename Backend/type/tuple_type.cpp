//
// Created by BALL on 2023/1/26.
//

#include "tuple_type.h"

#include <utility>

using namespace type;

TupleType::TupleType(std::initializer_list<UnitType> tuple) {
    for (auto element: tuple) {
        types.push_back(element);
    }
}
TupleType::TupleType(std::vector<UnitType> tuple): types(std::move(tuple)) {}

std::string TupleType::to_string() {
    std::string content = "(";
    for (auto element: types) {
        content += element.to_string();
        content += ", ";
    }
    content.erase(content.end());content.erase(content.end());
    content += ")";

    return content;
}