//
// Created by BALL on 2022/12/25.
//

#ifndef SAKORA_BASIC_TYPE_H
#define SAKORA_BASIC_TYPE_H

#include "../visitor/visitor.h"

namespace type {
    // Enumeration of basic data types
    enum BasicType {
        Int16,   // 16-bit integer
        Int32,   // 32-bit integer
        Int64,   // 64-bit integer
        Float,   // single precision floating point number
        Double,  // double precision floating point number
        Boolean, // boolean value
        String,  // string
        Typeid,  // typeid
        Object   // object
    };

    enum StorageKind {
        Ref, // indicating value is stored as a reference
        Val // indicating value is stored as a value
    };

    // Enumeration representing the structure of an object
    enum Structure {
        Normal, // normal value
        List,   // list
        Struct, // struct
        StructArray // struct array
    };

    // Struct representing a data type
    struct UnitType {
        BasicType basic;       // basic type of the object
        Structure st;          // structure of the object
        StorageKind stk;       // storage of the object

        // Constructors
        UnitType() = default;                      // default constructor
        UnitType(BasicType b);                     // construct with basic type
        UnitType(BasicType b, Structure s);        // construct with basic type, ownership, modifier, and structure
        UnitType(BasicType b, Structure s, StorageKind stok);

        std::string to_string();
    };

}

#endif //SAKORA_BASIC_TYPE_H
