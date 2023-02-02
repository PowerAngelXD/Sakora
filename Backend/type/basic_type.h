//
// Created by BALL on 2022/12/25.
//

#ifndef SAKORA_BASIC_TYPE_H
#define SAKORA_BASIC_TYPE_H

#include "../visitor/visitor.h"

namespace type {
    // Enumeration of basic data types
    enum BasicType {
        Integer, // integer-64bit
        Decimal, // decimal-double
        Boolean, // boolean value
        String,  // string
        Typeid,  // typeid
    };

    enum StorageKind {
        Ref, // indicating value is stored as a reference
        Val // indicating value is stored as a value
    };

    // Struct representing a data type
    struct UnitType {
        BasicType basic;       // basic type of the object
        StorageKind stk;       // storage of the object

        // Constructors
        UnitType() = default;                      // default constructor
        UnitType(BasicType b);                     // construct with basic type
        UnitType(BasicType b, StorageKind stok);

        std::string to_string();
    };

}

#endif //SAKORA_BASIC_TYPE_H
