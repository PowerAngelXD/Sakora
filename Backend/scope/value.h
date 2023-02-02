//
// Created by BALL on 2022/12/26.
//

#ifndef SAKORA_VALUE_H
#define SAKORA_VALUE_H

#include "../type/type.h"
#include "../../error/storage_error.h"
#include <cmath>
#include <float.h>
#include <cstring>

#define float_equ(a,b) ((fabs((a) - (b)) < (1e-8))
#define INT(val) *(long long*)val
#define DECI(val) *(double*)val
#define STR(val) *(std::string*)val
#define BOOL(val) *(bool*)val
#define TYPEID(val) *(type::Type*)val


namespace storage {
    // Check whether two floating point numbers are equal
    bool doubleEqual(double d1, double d2);

    // Val class represents a value in the program, which could be a basic type or a user-defined type
    class Val {
        // Pointer to the value stored in this Val object
        void* val_ptr = nullptr;
        // Size of the value stored in this Val object
        size_t val_size = 0;
        // UnitType of the value stored in this Val object
        type::Type val_type;

        int line, column;
    public:
        // Default constructor that creates an empty Val object with no value
        Val()=default;

        // Constructors to create a Val object with a basic type value of the given type
        Val(long long v);
        Val(double v);
        Val(bool v);
        Val(std::string v);
        Val(type::UnitType v);

        // Constructor to create a Val object with a value of the given type and a polonger to the value
        template<typename T>
        Val(T v, type::Type t);

        // Operators to perform arithmetic and comparison operations on Val objects
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
        Val operator ||(Val v);
        Val operator &&(Val v);
        Val operator! ();

        // Set value line and column
        void setLnCol(int ln, int col);
        // Returns the basic type of the value stored in this Val object (e.g. long, Float, Bool)
        type::BasicType getBasicType() const;
        // Returns the type of the value stored in this Val object (could be a basic type or a user-defined type)
        type::Type getType() const;
        // Returns a pointer to the value stored in this Val object
        void* val();
        // Deallocates the memory used by the value stored in this Val object
        void freeVal();
    };

}

#endif //SAKORA_VALUE_H
