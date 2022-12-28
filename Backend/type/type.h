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
        Object   // object
    };

    // Determines how values are stored, referenced or valued
    enum StorageKind {
        // The `Val` enumerator represents the value storage kind, which means that the value is stored directly in the enumeration.
        Val,
        // The `Ref` enumerator represents the reference storage kind, which means that the value is stored in a separate location and the enumeration holds a reference to it.
        Ref,
    };

    // Enumeration representing the structure of an object
    enum Structure {
        Normal, // normal value
        List,   // list
        Struct, // struct
        Tuple   // tuple
    };

    // Struct representing a data type
    struct Type {
        BasicType basic;       // basic type of the object
        StorageKind ownership;     // ownership of the object
        Structure st;          // structure of the object

        // Constructors
        Type() = default;                      // default constructor
        Type(BasicType b);                     // construct with basic type
        Type(BasicType basic, StorageKind ok);     // construct with basic type and ownership
        Type(BasicType basic, StorageKind ok, Structure s); // construct with basic type, ownership, modifier, and structure
    };

}

#endif //SAKORA_TYPE_H
