//
// Created by BALL on 2023/3/6.
//

#ifndef SAKORA_SINTEGER_H
#define SAKORA_SINTEGER_H

#include "../basic_type.h"

namespace type {
    enum IntKind {
        i32, i64
    };

    class SInteger {
        IntKind ikind = i32;

        int* i32_num = nullptr;
        long long* i64_num = nullptr;

    public:
        SInteger(int n);
        SInteger(long long n);

        IntKind getKind();
        int getI32();
        long long getI64();
    };
}

#endif //SAKORA_SINTEGER_H
