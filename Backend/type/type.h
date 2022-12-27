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

    // Enumeration representing ownership of an object
    enum OwnKind {
        Ref, // reference
        Own  // owned object
    };

    // Enumeration of modifiers
    enum Modifier {
        Const,    // constant value
        Dynamic,  // dynamically allocated object
        Static    // statically allocated object
    };

    // Enumeration representing the structure of an object
    enum Structure {
        Normal, // normal object
        List,   // list
        Struct, // struct
        Tuple   // tuple
    };

    // Struct representing a data type
    struct Type {
        BasicType basic;       // basic type of the object
        OwnKind ownership;     // ownership of the object
        Modifier mod;          // modifier of the object
        Structure st;          // structure of the object

        // Constructors
        Type() = default;                      // default constructor
        Type(BasicType b);                     // construct with basic type
        Type(BasicType basic, OwnKind ok);     // construct with basic type and ownership
        Type(BasicType basic, OwnKind ok, Modifier m); // construct with basic type, ownership, and modifier
        Type(BasicType basic, OwnKind ok, Modifier m, Structure s); // construct with basic type, ownership, modifier, and structure
    };

}

#endif //SAKORA_TYPE_H
