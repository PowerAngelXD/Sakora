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
#define FLAG(val) *(visitor::FlagValue*)val


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
        Val(visitor::FlagValue flag);
        Val(const std::vector<Val>& list, bool is_mutable = false);

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
        [[nodiscard]] type::BasicType getBasicType() const;
        // Returns the type of the value stored in this Val object (could be a basic type or a user-defined type)
        [[nodiscard]] type::Type getType() const;
        // Get the head type
        [[nodiscard]] type::UnitType* getHeadType() const;
        // Returns a pointer to the value stored in this Val object
        void* get_ptr();
        // Deallocates the memory used by the value stored in this Val object
        void freeVal();
        // Print the value
        void debugPrint(bool is_repr);
        // Returns a value recommended
        long long int_val();
        double deci_val();
        bool bool_val();
        std::string str_val();
        visitor::FlagValue flag_val();
        type::Type valtype_val();
        // Null check
        bool is_null();
    };

}

#endif //SAKORA_VALUE_H
