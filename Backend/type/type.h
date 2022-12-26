//
// Created by BALL on 2022/12/25.
//

#ifndef SAKORA_TYPE_H
#define SAKORA_TYPE_H

#include "../visitor/visitor.h"

namespace type {
    enum BasicType {
        Int16, Int32, Int64,
        Float, Double,
        Boolean,
        String,
        Object
    };

    enum OwnKind {
        Ref, Own
    };

    enum Modifier {
        Const,
        Dynamic, Static,
    };

    enum Structure {
        Normal, List, Struct, Tuple
    };

    struct Type {
        BasicType basic;
        OwnKind ownership;
        Modifier mod;
        Structure st;

        Type()=default;
        Type(BasicType b);
        Type(BasicType basic, OwnKind ok);
        Type(BasicType basic, OwnKind ok, Modifier m);
        Type(BasicType basic, OwnKind ok, Modifier m, Structure s);
    };
}

#endif //SAKORA_TYPE_H
