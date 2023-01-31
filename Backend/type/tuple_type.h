//
// Created by BALL on 2023/1/26.
//

#ifndef SAKORA_TUPLE_TYPE_H
#define SAKORA_TUPLE_TYPE_H

#include "basic_type.h"

namespace type {
    struct TupleType {
        std::vector<UnitType> types;

        TupleType(std::initializer_list<UnitType> tuple);
        TupleType(std::vector<UnitType> tuple);

        std::string to_string();
    };
}

#endif //SAKORA_TUPLE_TYPE_H
