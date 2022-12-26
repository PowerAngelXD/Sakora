//
// Created by BALL on 2022/12/26.
//

#ifndef SAKORA_VALUE_H
#define SAKORA_VALUE_H

#include "../type/type.h"
#include <cmath>

#define float_equ(a,b) ((fabs((a) - (b)) < (1e-8))

namespace storage {
    class Val {
        void* val_ptr;
        size_t val_size;
        type::Type val_type;
    public:
        Val(short v);
        Val(int v);
        Val(long long v);
        Val(float v);
        Val(double v);
        Val(bool v);
        Val(std::string v);

        template<typename T>
        Val(T v, type::Type t);

        Val operator+ (Val v);
        Val operator- (Val v);
        Val operator* (Val v);
        Val operator/ (Val v);
        Val operator% (Val v);
        Val operator== (Val v);
        Val operator!= (Val v);
        Val operator< (Val v);
        Val operator> (Val v);
        Val operator<= (Val v);
        Val operator>= (Val v);
        Val operator! ();

        [[nodiscard]] type::BasicType getBasicType() const;
        [[nodiscard]] type::Type getType() const;
        void* val();
    };
}

#endif //SAKORA_VALUE_H
