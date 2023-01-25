//
// Created by BALL on 2022/12/25.
//

#ifndef SAKORA_TYPE_H
#define SAKORA_TYPE_H

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
        StructArray, // struct array
        Tuple   // tuple
    };

    // Struct representing a data type
    struct Type {
        BasicType basic;       // basic type of the object
        Structure st;          // structure of the object
        StorageKind stk;       // storage of the object

        // Constructors
        Type() = default;                      // default constructor
        Type(BasicType b);                     // construct with basic type
        Type(BasicType b, Structure s);        // construct with basic type, ownership, modifier, and structure
        Type(BasicType b, Structure s, StorageKind stok);
    };

}

#endif //SAKORA_TYPE_H
