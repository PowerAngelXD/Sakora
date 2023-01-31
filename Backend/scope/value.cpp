//
// Created by BALL on 2022/12/26.
//

#include "value.h"

#include <utility>

using namespace storage;

Val::Val(int v) {
    val_size = sizeof(int);
    val_ptr = (void*)new decltype(v);
    memcpy(val_ptr, &v, val_size);
    val_type = type::UnitType(type::BasicType::Int16);
}
Val::Val(long v) {
    val_size = sizeof(long);
    val_ptr = (void*)new decltype(v);
    memcpy(val_ptr, &v, val_size);
    val_type = type::UnitType(type::BasicType::Int32);
}
Val::Val(long long v) {
    val_size = sizeof(long long);
    val_ptr = (void*)new decltype(v);
    memcpy(val_ptr, &v, val_size);
    val_type = type::UnitType(type::BasicType::Int64);
}
Val::Val(float v) {
    val_size = sizeof(float);
    val_ptr = (void*)new decltype(v);
    memcpy(val_ptr, &v, val_size);
    val_type = type::UnitType(type::BasicType::Float);
}
Val::Val(double v) {
    val_size = sizeof(double);
    val_ptr = (void*)new decltype(v);
    memcpy(val_ptr, &v, val_size);
    val_type = type::UnitType(type::BasicType::Double);
}
Val::Val(bool v) {
    val_size = sizeof(bool);
    val_ptr = (void*)new decltype(v);
    memcpy(val_ptr, &v, val_size);
    val_type = type::UnitType(type::BasicType::Boolean);
}
Val::Val(std::string v) {
    val_size = sizeof(std::string);
    val_ptr = new std::string;
    *(std::string*)val_ptr = std::move(v);
    val_type = type::UnitType(type::BasicType::String);
}
Val::Val(type::UnitType v) {
    val_size = sizeof(type::UnitType);
    val_ptr = (void*)new decltype(v);
    memcpy(val_ptr, &v, val_size);
    val_type = type::UnitType(type::BasicType::Typeid);
}

template<typename T>
Val::Val(T v, type::UnitType t) {
    val_size = sizeof(T);
    val_ptr = (void*)new decltype(v);
    memcpy(val_ptr, &v, val_size);
    val_type = t;
}

Val Val::operator+ (Val v) {
    switch (this->val_type.basic) {
        case type::Int16:
            switch (v.val_type.basic) {
                case type::Int16: return {*(int*)this->val_ptr + *(int*)v.val_ptr};
                case type::Int32: return {*(int*)this->val_ptr + *(long*)v.val_ptr};
                case type::Int64: return {*(int*)this->val_ptr + *(long long*)v.val_ptr};
                case type::Float: return {static_cast<float>(*(int*)this->val_ptr) + *(float*)v.val_ptr};
                case type::Double: return {*(int*)this->val_ptr + *(double*)v.val_ptr};
                case type::String: case type::Boolean:   case type::Typeid: break;
            }
            break;
        case type::Int32:
            switch (v.val_type.basic) {
                case type::Int16: return {*(long*)this->val_ptr + *(int*)v.val_ptr};
                case type::Int32: return {*(long*)this->val_ptr + *(long*)v.val_ptr};
                case type::Int64: return {*(long*)this->val_ptr + *(long long*)v.val_ptr};
                case type::Float: return {static_cast<float>(*(long*)this->val_ptr) + *(float*)v.val_ptr};
                case type::Double: return {*(long*)this->val_ptr + *(double*)v.val_ptr};
                case type::String: case type::Boolean:   case type::Typeid: break;
            }
            break;
        case type::Int64:
            switch (v.val_type.basic) {
                case type::Int16: return {*(long*)this->val_ptr + *(int*)v.val_ptr};
                case type::Int32: return {*(long*)this->val_ptr + *(long*)v.val_ptr};
                case type::Int64: return {*(long*)this->val_ptr + *(long long*)v.val_ptr};
                case type::Float: return {static_cast<float>(*(long*)this->val_ptr) + *(float*)v.val_ptr};
                case type::Double: return {*(long*)this->val_ptr + *(double*)v.val_ptr};
                case type::String: case type::Boolean:   case type::Typeid: break;
            }
            break;
        case type::Float:
            switch (v.val_type.basic) {
                case type::Int16: return {*(float*)this->val_ptr + static_cast<float>(*(int *) v.val_ptr)};
                case type::Int32: return {*(float*)this->val_ptr + static_cast<float>(*(long*)v.val_ptr)};
                case type::Int64: return {*(float*)this->val_ptr + static_cast<float>(*(long long*)v.val_ptr)};
                case type::Float: return {*(float*)this->val_ptr + *(float*)v.val_ptr};
                case type::Double: return {*(float*)this->val_ptr + *(double*)v.val_ptr};
                case type::String: case type::Boolean:   case type::Typeid: break;
            }
            break;
        case type::Double:
            switch (v.val_type.basic) {
                case type::Int16: return {*(double*)this->val_ptr + *(int*)v.val_ptr};
                case type::Int32: return {*(double*)this->val_ptr + *(long*)v.val_ptr};
                case type::Int64: return {*(double*)this->val_ptr + static_cast<double>(*(long long*)v.val_ptr)};
                case type::Float: return {*(double*)this->val_ptr + *(float*)v.val_ptr};
                case type::Double: return {*(double*)this->val_ptr + *(double*)v.val_ptr};
                case type::String: case type::Boolean:   case type::Typeid: break;
            }
            break;
        case type::String:
            switch (v.val_type.basic) {
                    case type::String: return {*(std::string*)this->val_ptr + *(std::string*)v.val_ptr};
                case type::Int16: case type::Double: case type::Int32: case type::Int64: case type::Float:case type::Boolean:   case type::Typeid: break;
            }
            break;
        case type::Typeid:
        case type::Boolean:
         
            break;
    }
    return {0};
}
Val Val::operator- (Val v) {
    switch (this->val_type.basic) {
        case type::Int16:
            switch (v.val_type.basic) {
                case type::Int16: return {*(int*)this->val_ptr - *(int*)v.val_ptr};
                case type::Int32: return {*(int*)this->val_ptr - *(long*)v.val_ptr};
                case type::Int64: return {*(int*)this->val_ptr - *(long long*)v.val_ptr};
                case type::Float: return {static_cast<float>(*(int*)this->val_ptr) - *(float*)v.val_ptr};
                case type::Double: return {*(int*)this->val_ptr - *(double*)v.val_ptr};
                case type::String: case type::Boolean:   case type::Typeid: break;
            }
            break;
        case type::Int32:
            switch (v.val_type.basic) {
                case type::Int16: return {*(long*)this->val_ptr - *(int*)v.val_ptr};
                case type::Int32: return {*(long*)this->val_ptr - *(long*)v.val_ptr};
                case type::Int64: return {*(long*)this->val_ptr - *(long long*)v.val_ptr};
                case type::Float: return {static_cast<float>(*(long*)this->val_ptr) - *(float*)v.val_ptr};
                case type::Double: return {*(long*)this->val_ptr - *(double*)v.val_ptr};
                case type::String: case type::Boolean:   case type::Typeid: break;
            }
            break;
        case type::Int64:
            switch (v.val_type.basic) {
                case type::Int16: return {*(long*)this->val_ptr - *(int*)v.val_ptr};
                case type::Int32: return {*(long*)this->val_ptr - *(long*)v.val_ptr};
                case type::Int64: return {*(long*)this->val_ptr - *(long long*)v.val_ptr};
                case type::Float: return {static_cast<float>(*(long*)this->val_ptr) - *(float*)v.val_ptr};
                case type::Double: return {*(long*)this->val_ptr - *(double*)v.val_ptr};
                case type::String: case type::Boolean:   case type::Typeid: break;
            }
            break;
        case type::Float:
            switch (v.val_type.basic) {
                case type::Int16: return {*(float*)this->val_ptr - static_cast<float>(*(int *) v.val_ptr)};
                case type::Int32: return {*(float*)this->val_ptr - static_cast<float>(*(long*)v.val_ptr)};
                case type::Int64: return {*(float*)this->val_ptr - static_cast<float>(*(long long*)v.val_ptr)};
                case type::Float: return {*(float*)this->val_ptr - *(float*)v.val_ptr};
                case type::Double: return {*(float*)this->val_ptr - *(double*)v.val_ptr};
                case type::String: case type::Boolean:   case type::Typeid: break;
            }
            break;
        case type::Double:
            switch (v.val_type.basic) {
                case type::Int16: return {*(double*)this->val_ptr - *(int*)v.val_ptr};
                case type::Int32: return {*(double*)this->val_ptr - *(long*)v.val_ptr};
                case type::Int64: return {*(double*)this->val_ptr - static_cast<double>(*(long long*)v.val_ptr)};
                case type::Float: return {*(double*)this->val_ptr - *(float*)v.val_ptr};
                case type::Double: return {*(double*)this->val_ptr - *(double*)v.val_ptr};
                case type::String: case type::Boolean:   case type::Typeid: break;
            }
            break;
        case type::String:
        case type::Boolean:
         
        case type::Typeid:
            break;
    }
    return {0};
}
Val Val::operator* (Val v) {
    switch (this->val_type.basic) {
        case type::Int16:
            switch (v.val_type.basic) {
                case type::Int16: return {*(int*)this->val_ptr * *(int*)v.val_ptr};
                case type::Int32: return {*(int*)this->val_ptr * *(long*)v.val_ptr};
                case type::Int64: return {*(int*)this->val_ptr * *(long long*)v.val_ptr};
                case type::Float: return {static_cast<float>(*(int*)this->val_ptr) * *(float*)v.val_ptr};
                case type::Double: return {*(int*)this->val_ptr * *(double*)v.val_ptr};
                case type::String: case type::Boolean:   case type::Typeid: break;
            }
            break;
        case type::Int32:
            switch (v.val_type.basic) {
                case type::Int16: return {*(long*)this->val_ptr * *(int*)v.val_ptr};
                case type::Int32: return {*(long*)this->val_ptr * *(long*)v.val_ptr};
                case type::Int64: return {*(long*)this->val_ptr * *(long long*)v.val_ptr};
                case type::Float: return {static_cast<float>(*(long*)this->val_ptr) * *(float*)v.val_ptr};
                case type::Double: return {*(long*)this->val_ptr * *(double*)v.val_ptr};
                case type::String: case type::Boolean:   case type::Typeid: break;
            }
            break;
        case type::Int64:
            switch (v.val_type.basic) {
                case type::Int16: return {*(long*)this->val_ptr * *(int*)v.val_ptr};
                case type::Int32: return {*(long*)this->val_ptr * *(long*)v.val_ptr};
                case type::Int64: return {*(long*)this->val_ptr * *(long long*)v.val_ptr};
                case type::Float: return {static_cast<float>(*(long*)this->val_ptr) * *(float*)v.val_ptr};
                case type::Double: return {*(long*)this->val_ptr * *(double*)v.val_ptr};
                case type::String: case type::Boolean:   case type::Typeid: break;
            }
            break;
        case type::Float:
            switch (v.val_type.basic) {
                case type::Int16: return {*(float*)this->val_ptr * static_cast<float>(*(int *) v.val_ptr)};
                case type::Int32: return {*(float*)this->val_ptr * static_cast<float>(*(long*)v.val_ptr)};
                case type::Int64: return {*(float*)this->val_ptr * static_cast<float>(*(long long*)v.val_ptr)};
                case type::Float: return {*(float*)this->val_ptr * *(float*)v.val_ptr};
                case type::Double: return {*(float*)this->val_ptr * *(double*)v.val_ptr};
                case type::String: case type::Boolean:   case type::Typeid: break;
            }
            break;
        case type::Double:
            switch (v.val_type.basic) {
                case type::Int16: return {*(double*)this->val_ptr * *(int*)v.val_ptr};
                case type::Int32: return {*(double*)this->val_ptr * *(long*)v.val_ptr};
                case type::Int64: return {*(double*)this->val_ptr * static_cast<double>(*(long long*)v.val_ptr)};
                case type::Float: return {*(double*)this->val_ptr * *(float*)v.val_ptr};
                case type::Double: return {*(double*)this->val_ptr * *(double*)v.val_ptr};
                case type::String: case type::Boolean:   case type::Typeid: break;
            }
            break;
        case type::String:
        case type::Boolean:
         
        case type::Typeid:
            break;
    }
    return {0};
}
Val Val::operator/ (Val v) {
    switch (this->val_type.basic) {
        case type::Int16:
            switch (v.val_type.basic) {
                case type::Int16: return {*(int*)this->val_ptr / *(int*)v.val_ptr};
                case type::Int32: return {*(int*)this->val_ptr / *(long*)v.val_ptr};
                case type::Int64: return {*(int*)this->val_ptr / *(long long*)v.val_ptr};
                case type::Float: return {static_cast<float>(*(int*)this->val_ptr) / *(float*)v.val_ptr};
                case type::Double: return {*(int*)this->val_ptr / *(double*)v.val_ptr};
                case type::String: case type::Boolean:   case type::Typeid: break;
            }
            break;
        case type::Int32:
            switch (v.val_type.basic) {
                case type::Int16: return {*(long*)this->val_ptr / *(int*)v.val_ptr};
                case type::Int32: return {*(long*)this->val_ptr / *(long*)v.val_ptr};
                case type::Int64: return {*(long*)this->val_ptr / *(long long*)v.val_ptr};
                case type::Float: return {static_cast<float>(*(long*)this->val_ptr) / *(float*)v.val_ptr};
                case type::Double: return {*(long*)this->val_ptr / *(double*)v.val_ptr};
                case type::String: case type::Boolean:   case type::Typeid: break;
            }
            break;
        case type::Int64:
            switch (v.val_type.basic) {
                case type::Int16: return {*(long*)this->val_ptr / *(int*)v.val_ptr};
                case type::Int32: return {*(long*)this->val_ptr / *(long*)v.val_ptr};
                case type::Int64: return {*(long*)this->val_ptr / *(long long*)v.val_ptr};
                case type::Float: return {static_cast<float>(*(long*)this->val_ptr) / *(float*)v.val_ptr};
                case type::Double: return {*(long*)this->val_ptr / *(double*)v.val_ptr};
                case type::String: case type::Boolean:   case type::Typeid: break;
            }
            break;
        case type::Float:
            switch (v.val_type.basic) {
                case type::Int16: return {*(float*)this->val_ptr / static_cast<float>(*(int *) v.val_ptr)};
                case type::Int32: return {*(float*)this->val_ptr / static_cast<float>(*(long*)v.val_ptr)};
                case type::Int64: return {*(float*)this->val_ptr / static_cast<float>(*(long long*)v.val_ptr)};
                case type::Float: return {*(float*)this->val_ptr / *(float*)v.val_ptr};
                case type::Double: return {*(float*)this->val_ptr / *(double*)v.val_ptr};
                case type::String: case type::Boolean:   case type::Typeid: break;
            }
            break;
        case type::Double:
            switch (v.val_type.basic) {
                case type::Int16: return {*(double*)this->val_ptr / *(int*)v.val_ptr};
                case type::Int32: return {*(double*)this->val_ptr / *(long*)v.val_ptr};
                case type::Int64: return {*(double*)this->val_ptr / static_cast<double>(*(long long*)v.val_ptr)};
                case type::Float: return {*(double*)this->val_ptr / *(float*)v.val_ptr};
                case type::Double: return {*(double*)this->val_ptr / *(double*)v.val_ptr};
                case type::String: case type::Boolean:   case type::Typeid: break;
            }
            break;
        case type::String:
        case type::Boolean:
         
        case type::Typeid:
            break;
    }
    return {0};
}
Val Val::operator% (Val v) {
    switch (this->val_type.basic) {
        case type::Int16:
            switch (v.val_type.basic) {
                case type::Int16: return {*(int*)this->val_ptr % *(int*)v.val_ptr};
                case type::Int32: return {*(int*)this->val_ptr % *(long*)v.val_ptr};
                case type::Int64: return {*(int*)this->val_ptr % *(long long*)v.val_ptr};
                case type::Float: case type::Double: case type::String: case type::Boolean:   case type::Typeid: break;
            }
            break;
        case type::Int32:
            switch (v.val_type.basic) {
                case type::Int16: return {*(long*)this->val_ptr % *(int*)v.val_ptr};
                case type::Int32: return {*(long*)this->val_ptr % *(long*)v.val_ptr};
                case type::Int64: return {*(long*)this->val_ptr % *(long long*)v.val_ptr};
                case type::Float: case type::Double: case type::String: case type::Boolean:   case type::Typeid: break;
            }
            break;
        case type::Int64:
            switch (v.val_type.basic) {
                case type::Int16: return {*(long*)this->val_ptr % *(int*)v.val_ptr};
                case type::Int32: return {*(long*)this->val_ptr % *(long*)v.val_ptr};
                case type::Int64: return {*(long*)this->val_ptr % *(long long*)v.val_ptr};
                case type::Float: case type::Double: case type::String: case type::Boolean:   case type::Typeid: break;
            }
            break;
        case type::Float:
        case type::Double:
        case type::String:
        case type::Boolean:
         
        case type::Typeid:
            break;
    }
    return {0};
}
Val Val::operator== (Val v) {
    switch (this->val_type.basic) {
        case type::Int16:
            switch (v.val_type.basic) {
                case type::Int16: return {*(int*)this->val_ptr == *(int*)v.val_ptr};
                case type::Int32: return {*(int*)this->val_ptr == *(long*)v.val_ptr};
                case type::Int64: return {*(int*)this->val_ptr == *(long long*)v.val_ptr};
                case type::Float: return {float_equ(static_cast<float>(*(int*)this->val_ptr), *(float*)v.val_ptr))};
                case type::Double: return {float_equ(*(int*)this->val_ptr, *(double*)v.val_ptr))};
                case type::Boolean: return {*(int*)this->val_ptr == *(bool*)v.val_ptr};
                case type::String:   case type::Typeid: break;
            }
            break;
        case type::Int32:
            switch (v.val_type.basic) {
                case type::Int16: return {*(long*)this->val_ptr == *(int*)v.val_ptr};
                case type::Int32: return {*(long*)this->val_ptr == *(long*)v.val_ptr};
                case type::Int64: return {*(long*)this->val_ptr == *(long long*)v.val_ptr};
                case type::Float: return {float_equ(static_cast<float>(*(long*)this->val_ptr), *(float*)v.val_ptr))};
                case type::Double: return {float_equ(*(long*)this->val_ptr, *(double*)v.val_ptr))};
                case type::Boolean: return {*(long*)this->val_ptr == *(bool*)v.val_ptr};
                case type::String:   case type::Typeid: break;
            }
            break;
        case type::Int64:
            switch (v.val_type.basic) {
                case type::Int16: return {*(long long*)this->val_ptr == *(int*)v.val_ptr};
                case type::Int32: return {*(long long*)this->val_ptr == *(long*)v.val_ptr};
                case type::Int64: return {*(long long*)this->val_ptr == *(long long*)v.val_ptr};
                case type::Float: return {float_equ(static_cast<float>(*(long long*)this->val_ptr), *(float*)v.val_ptr))};
                case type::Double: return {float_equ(static_cast<double>(*(long long*)this->val_ptr), *(double*)v.val_ptr))};
                case type::Boolean: return {*(long long*)this->val_ptr == *(bool*)v.val_ptr};
                case type::String:   case type::Typeid: break;
            }
            break;
        case type::Float:
            switch (v.val_type.basic) {
                case type::Int16: return {float_equ(*(float*)this->val_ptr, static_cast<float>(*(int *) v.val_ptr)))};
                case type::Int32: return {float_equ(*(float*)this->val_ptr, static_cast<float>(*(long*)v.val_ptr)))};
                case type::Int64: return {float_equ(*(float*)this->val_ptr, static_cast<float>(*(long long*)v.val_ptr)))};
                case type::Float: return {float_equ(*(float*)this->val_ptr, *(float*)v.val_ptr))};
                case type::Double: return {float_equ(*(float*)this->val_ptr, *(double*)v.val_ptr))};
                case type::Boolean: return {float_equ(*(float*)this->val_ptr, *(bool*)v.val_ptr))};
                case type::String:   case type::Typeid: break;
            }
            break;
        case type::Double:
            switch (v.val_type.basic) {
                case type::Int16: return {float_equ(*(double*)this->val_ptr, *(int*)v.val_ptr))};
                case type::Int32: return {float_equ(*(double*)this->val_ptr, static_cast<float>(*(long*)v.val_ptr)))};
                case type::Int64: return {float_equ(*(double*)this->val_ptr, static_cast<float>(*(long long*)v.val_ptr)))};
                case type::Float: return {float_equ(*(double*)this->val_ptr, *(float*)v.val_ptr))};
                case type::Double: return {float_equ(*(double*)this->val_ptr, *(double*)v.val_ptr))};
                case type::Boolean: return {float_equ(*(double*)this->val_ptr, *(bool*)v.val_ptr))};
                case type::String:   case type::Typeid: break;
            }
            break;
        case type::String:
            switch (v.val_type.basic) {
                        case type::String: return {*(std::string*)this->val_ptr == *(std::string*)v.val_ptr};
                case type::Int16: case type::Double: case type::Int32: case type::Int64: case type::Float:case type::Boolean:   case type::Typeid: break;
            }
            break;
        case type::Boolean:
            switch (v.val_type.basic) {
                case type::Boolean: return {*(bool*)this->val_ptr == *(bool*)v.val_ptr};
                case type::Int16: case type::Double: case type::Int32: case type::Int64: case type::Float:case type::String:   case type::Typeid: break;
            }
            break;
         
        case type::Typeid:
            break;
    }
    return {0};
}
Val Val::operator!= (Val v) {
    switch (this->val_type.basic) {
        case type::Int16:
            switch (v.val_type.basic) {
                case type::Int16: return {*(int*)this->val_ptr != *(int*)v.val_ptr};
                case type::Int32: return {*(int*)this->val_ptr != *(long*)v.val_ptr};
                case type::Int64: return {*(int*)this->val_ptr != *(long long*)v.val_ptr};
                case type::Float: return {!float_equ(static_cast<float>(*(int*)this->val_ptr), *(float*)v.val_ptr))};
                case type::Double: return {!float_equ(*(int*)this->val_ptr, *(double*)v.val_ptr))};
                case type::Boolean: return {*(int*)this->val_ptr != *(bool*)v.val_ptr};
                case type::String:   case type::Typeid: break;
            }
            break;
        case type::Int32:
            switch (v.val_type.basic) {
                case type::Int16: return {*(long*)this->val_ptr != *(int*)v.val_ptr};
                case type::Int32: return {*(long*)this->val_ptr != *(long*)v.val_ptr};
                case type::Int64: return {*(long*)this->val_ptr != *(long long*)v.val_ptr};
                case type::Float: return {!float_equ(static_cast<float>(*(long*)this->val_ptr), *(float*)v.val_ptr))};
                case type::Double: return {!float_equ(*(long*)this->val_ptr, *(double*)v.val_ptr))};
                case type::Boolean: return {*(long*)this->val_ptr != *(bool*)v.val_ptr};
                case type::String:   case type::Typeid: break;
            }
            break;
        case type::Int64:
            switch (v.val_type.basic) {
                case type::Int16: return {*(long long*)this->val_ptr != *(int*)v.val_ptr};
                case type::Int32: return {*(long long*)this->val_ptr != *(long*)v.val_ptr};
                case type::Int64: return {*(long long*)this->val_ptr != *(long long*)v.val_ptr};
                case type::Float: return {!float_equ(static_cast<float>(*(long long*)this->val_ptr), *(float*)v.val_ptr))};
                case type::Double: return {!float_equ(static_cast<double>(*(long long*)this->val_ptr), *(double*)v.val_ptr))};
                case type::Boolean: return {*(long long*)this->val_ptr != *(bool*)v.val_ptr};
                case type::String:   case type::Typeid: break;
            }
            break;
        case type::Float:
            switch (v.val_type.basic) {
                case type::Int16: return {!float_equ(*(float*)this->val_ptr, static_cast<float>(*(int *) v.val_ptr)))};
                case type::Int32: return {!float_equ(*(float*)this->val_ptr, static_cast<float>(*(long*)v.val_ptr)))};
                case type::Int64: return {!float_equ(*(float*)this->val_ptr, static_cast<float>(*(long long*)v.val_ptr)))};
                case type::Float: return {!float_equ(*(float*)this->val_ptr, *(float*)v.val_ptr))};
                case type::Double: return {!float_equ(*(float*)this->val_ptr, *(double*)v.val_ptr))};
                case type::Boolean: return {!float_equ(*(float*)this->val_ptr, *(bool*)v.val_ptr))};
                case type::String:   case type::Typeid: break;
            }
            break;
        case type::Double:
            switch (v.val_type.basic) {
                case type::Int16: return {!float_equ(*(double*)this->val_ptr, *(int*)v.val_ptr))};
                case type::Int32: return {!float_equ(*(double*)this->val_ptr, static_cast<float>(*(long*)v.val_ptr)))};
                case type::Int64: return {!float_equ(*(double*)this->val_ptr, static_cast<float>(*(long long*)v.val_ptr)))};
                case type::Float: return {!float_equ(*(double*)this->val_ptr, *(float*)v.val_ptr))};
                case type::Double: return {!float_equ(*(double*)this->val_ptr, *(double*)v.val_ptr))};
                case type::Boolean: return {!float_equ(*(double*)this->val_ptr, *(bool*)v.val_ptr))};
                case type::String:   case type::Typeid: break;
            }
            break;
        case type::String:
            switch (v.val_type.basic) {
                case type::String: return {*(std::string*)this->val_ptr != *(std::string*)v.val_ptr};
                case type::Int16: case type::Double: case type::Int32: case type::Int64: case type::Float:case type::Boolean:   case type::Typeid: break;
            }
            break;
        case type::Boolean:
            switch (v.val_type.basic) {
                case type::Boolean: return {*(bool*)this->val_ptr != *(bool*)v.val_ptr};
                case type::Int16: case type::Double: case type::Int32: case type::Int64: case type::Float:case type::String:   case type::Typeid: break;
            }
            break;
         
        case type::Typeid:
            break;
    }
    return {0};
}
Val Val::operator< (Val v) {
    switch (this->val_type.basic) {
        case type::Int16:
            switch (v.val_type.basic) {
                case type::Int16: return {*(int*)this->val_ptr < *(int*)v.val_ptr};
                case type::Int32: return {*(int*)this->val_ptr < *(long*)v.val_ptr};
                case type::Int64: return {*(int*)this->val_ptr < *(long long*)v.val_ptr};
                case type::Float: return {static_cast<float>(*(int*)this->val_ptr) < *(float*)v.val_ptr};
                case type::Double: return {*(int*)this->val_ptr < *(double*)v.val_ptr};
                case type::String: case type::Boolean:   case type::Typeid: break;
            }
            break;
        case type::Int32:
            switch (v.val_type.basic) {
                case type::Int16: return {*(long*)this->val_ptr < *(int*)v.val_ptr};
                case type::Int32: return {*(long*)this->val_ptr < *(long*)v.val_ptr};
                case type::Int64: return {*(long*)this->val_ptr < *(long long*)v.val_ptr};
                case type::Float: return {static_cast<float>(*(long*)this->val_ptr) < *(float*)v.val_ptr};
                case type::Double: return {*(long*)this->val_ptr < *(double*)v.val_ptr};
                case type::String: case type::Boolean:   case type::Typeid: break;
            }
            break;
        case type::Int64:
            switch (v.val_type.basic) {
                case type::Int16: return {*(long*)this->val_ptr < *(int*)v.val_ptr};
                case type::Int32: return {*(long*)this->val_ptr < *(long*)v.val_ptr};
                case type::Int64: return {*(long*)this->val_ptr < *(long long*)v.val_ptr};
                case type::Float: return {static_cast<float>(*(long*)this->val_ptr) < *(float*)v.val_ptr};
                case type::Double: return {*(long*)this->val_ptr < *(double*)v.val_ptr};
                case type::String: case type::Boolean:   case type::Typeid: break;
            }
            break;
        case type::Float:
            switch (v.val_type.basic) {
                case type::Int16: return {*(float*)this->val_ptr < static_cast<float>(*(int *) v.val_ptr)};
                case type::Int32: return {*(float*)this->val_ptr < static_cast<float>(*(long*)v.val_ptr)};
                case type::Int64: return {*(float*)this->val_ptr < static_cast<float>(*(long long*)v.val_ptr)};
                case type::Float: return {*(float*)this->val_ptr < *(float*)v.val_ptr};
                case type::Double: return {*(float*)this->val_ptr < *(double*)v.val_ptr};
                case type::String: case type::Boolean:   case type::Typeid: break;
            }
            break;
        case type::Double:
            switch (v.val_type.basic) {
                case type::Int16: return {*(double*)this->val_ptr < *(int*)v.val_ptr};
                case type::Int32: return {*(double*)this->val_ptr < *(long*)v.val_ptr};
                case type::Int64: return {*(double*)this->val_ptr < static_cast<double>(*(long long*)v.val_ptr)};
                case type::Float: return {*(double*)this->val_ptr < *(float*)v.val_ptr};
                case type::Double: return {*(double*)this->val_ptr < *(double*)v.val_ptr};
                case type::String: case type::Boolean:   case type::Typeid: break;
            }
            break;
        case type::String:
        case type::Boolean:
         
        case type::Typeid:
            break;
    }
    return {0};
}
Val Val::operator> (Val v) {
    switch (this->val_type.basic) {
        case type::Int16:
            switch (v.val_type.basic) {
                case type::Int16: return {*(int*)this->val_ptr > *(int*)v.val_ptr};
                case type::Int32: return {*(int*)this->val_ptr > *(long*)v.val_ptr};
                case type::Int64: return {*(int*)this->val_ptr > *(long long*)v.val_ptr};
                case type::Float: return {static_cast<float>(*(int*)this->val_ptr) > *(float*)v.val_ptr};
                case type::Double: return {*(int*)this->val_ptr > *(double*)v.val_ptr};
                case type::String: case type::Boolean:   case type::Typeid: break;
            }
            break;
        case type::Int32:
            switch (v.val_type.basic) {
                case type::Int16: return {*(long*)this->val_ptr > *(int*)v.val_ptr};
                case type::Int32: return {*(long*)this->val_ptr > *(long*)v.val_ptr};
                case type::Int64: return {*(long*)this->val_ptr > *(long long*)v.val_ptr};
                case type::Float: return {static_cast<float>(*(long*)this->val_ptr) > *(float*)v.val_ptr};
                case type::Double: return {*(long*)this->val_ptr > *(double*)v.val_ptr};
                case type::String: case type::Boolean:   case type::Typeid: break;
            }
            break;
        case type::Int64:
            switch (v.val_type.basic) {
                case type::Int16: return {*(long*)this->val_ptr > *(int*)v.val_ptr};
                case type::Int32: return {*(long*)this->val_ptr > *(long*)v.val_ptr};
                case type::Int64: return {*(long*)this->val_ptr > *(long long*)v.val_ptr};
                case type::Float: return {static_cast<float>(*(long*)this->val_ptr) > *(float*)v.val_ptr};
                case type::Double: return {*(long*)this->val_ptr > *(double*)v.val_ptr};
                case type::String: case type::Boolean:   case type::Typeid: break;
            }
            break;
        case type::Float:
            switch (v.val_type.basic) {
                case type::Int16: return {*(float*)this->val_ptr > static_cast<float>(*(int *) v.val_ptr)};
                case type::Int32: return {*(float*)this->val_ptr > static_cast<float>(*(long*)v.val_ptr)};
                case type::Int64: return {*(float*)this->val_ptr > static_cast<float>(*(long long*)v.val_ptr)};
                case type::Float: return {*(float*)this->val_ptr > *(float*)v.val_ptr};
                case type::Double: return {*(float*)this->val_ptr > *(double*)v.val_ptr};
                case type::String: case type::Boolean:   case type::Typeid: break;
            }
            break;
        case type::Double:
            switch (v.val_type.basic) {
                case type::Int16: return {*(double*)this->val_ptr > *(int*)v.val_ptr};
                case type::Int32: return {*(double*)this->val_ptr > *(long*)v.val_ptr};
                case type::Int64: return {*(double*)this->val_ptr > static_cast<double>(*(long long*)v.val_ptr)};
                case type::Float: return {*(double*)this->val_ptr > *(float*)v.val_ptr};
                case type::Double: return {*(double*)this->val_ptr > *(double*)v.val_ptr};
                case type::String: case type::Boolean:   case type::Typeid: break;
            }
            break;
        case type::String:
        case type::Boolean:
         
        case type::Typeid:
            break;
    }
    return {0};
}
Val Val::operator<= (Val v) {
    switch (this->val_type.basic) {
        case type::Int16:
            switch (v.val_type.basic) {
                case type::Int16: return {*(int*)this->val_ptr <= *(int*)v.val_ptr};
                case type::Int32: return {*(int*)this->val_ptr <= *(long*)v.val_ptr};
                case type::Int64: return {*(int*)this->val_ptr <= *(long long*)v.val_ptr};
                case type::Float: return {static_cast<float>(*(int*)this->val_ptr) <= *(float*)v.val_ptr};
                case type::Double: return {*(int*)this->val_ptr <= *(double*)v.val_ptr};
                case type::String: case type::Boolean:   case type::Typeid: break;
            }
            break;
        case type::Int32:
            switch (v.val_type.basic) {
                case type::Int16: return {*(long*)this->val_ptr <= *(int*)v.val_ptr};
                case type::Int32: return {*(long*)this->val_ptr <= *(long*)v.val_ptr};
                case type::Int64: return {*(long*)this->val_ptr <= *(long long*)v.val_ptr};
                case type::Float: return {static_cast<float>(*(long*)this->val_ptr) <= *(float*)v.val_ptr};
                case type::Double: return {*(long*)this->val_ptr <= *(double*)v.val_ptr};
                case type::String: case type::Boolean:   case type::Typeid: break;
            }
            break;
        case type::Int64:
            switch (v.val_type.basic) {
                case type::Int16: return {*(long*)this->val_ptr <= *(int*)v.val_ptr};
                case type::Int32: return {*(long*)this->val_ptr <= *(long*)v.val_ptr};
                case type::Int64: return {*(long*)this->val_ptr <= *(long long*)v.val_ptr};
                case type::Float: return {static_cast<float>(*(long*)this->val_ptr) <= *(float*)v.val_ptr};
                case type::Double: return {*(long*)this->val_ptr <= *(double*)v.val_ptr};
                case type::String: case type::Boolean:   case type::Typeid: break;
            }
            break;
        case type::Float:
            switch (v.val_type.basic) {
                case type::Int16: return {*(float*)this->val_ptr <= static_cast<float>(*(int *) v.val_ptr)};
                case type::Int32: return {*(float*)this->val_ptr <= static_cast<float>(*(long*)v.val_ptr)};
                case type::Int64: return {*(float*)this->val_ptr <= static_cast<float>(*(long long*)v.val_ptr)};
                case type::Float: return {*(float*)this->val_ptr <= *(float*)v.val_ptr};
                case type::Double: return {*(float*)this->val_ptr <= *(double*)v.val_ptr};
                case type::String: case type::Boolean:   case type::Typeid: break;
            }
            break;
        case type::Double:
            switch (v.val_type.basic) {
                case type::Int16: return {*(double*)this->val_ptr <= *(int*)v.val_ptr};
                case type::Int32: return {*(double*)this->val_ptr <= *(long*)v.val_ptr};
                case type::Int64: return {*(double*)this->val_ptr <= static_cast<double>(*(long long*)v.val_ptr)};
                case type::Float: return {*(double*)this->val_ptr <= *(float*)v.val_ptr};
                case type::Double: return {*(double*)this->val_ptr <= *(double*)v.val_ptr};
                case type::String: case type::Boolean:   case type::Typeid: break;
            }
            break;
        case type::String:
        case type::Boolean:
         
        case type::Typeid:
            break;
    }
    return {0};
}
Val Val::operator>= (Val v) {
    switch (this->val_type.basic) {
        case type::Int16:
            switch (v.val_type.basic) {
                case type::Int16: return {*(int*)this->val_ptr >= *(int*)v.val_ptr};
                case type::Int32: return {*(int*)this->val_ptr >= *(long*)v.val_ptr};
                case type::Int64: return {*(int*)this->val_ptr >= *(long long*)v.val_ptr};
                case type::Float: return {static_cast<float>(*(int*)this->val_ptr) >= *(float*)v.val_ptr};
                case type::Double: return {*(int*)this->val_ptr >= *(double*)v.val_ptr};
                case type::String: case type::Boolean:   case type::Typeid: break;
            }
            break;
        case type::Int32:
            switch (v.val_type.basic) {
                case type::Int16: return {*(long*)this->val_ptr >= *(int*)v.val_ptr};
                case type::Int32: return {*(long*)this->val_ptr >= *(long*)v.val_ptr};
                case type::Int64: return {*(long*)this->val_ptr >= *(long long*)v.val_ptr};
                case type::Float: return {static_cast<float>(*(long*)this->val_ptr) >= *(float*)v.val_ptr};
                case type::Double: return {*(long*)this->val_ptr >= *(double*)v.val_ptr};
                case type::String: case type::Boolean:   case type::Typeid: break;
            }
            break;
        case type::Int64:
            switch (v.val_type.basic) {
                case type::Int16: return {*(long*)this->val_ptr >= *(int*)v.val_ptr};
                case type::Int32: return {*(long*)this->val_ptr >= *(long*)v.val_ptr};
                case type::Int64: return {*(long*)this->val_ptr >= *(long long*)v.val_ptr};
                case type::Float: return {static_cast<float>(*(long*)this->val_ptr) >= *(float*)v.val_ptr};
                case type::Double: return {*(long*)this->val_ptr >= *(double*)v.val_ptr};
                case type::String: case type::Boolean:   case type::Typeid: break;
            }
            break;
        case type::Float:
            switch (v.val_type.basic) {
                case type::Int16: return {*(float*)this->val_ptr >= static_cast<float>(*(int *) v.val_ptr)};
                case type::Int32: return {*(float*)this->val_ptr >= static_cast<float>(*(long*)v.val_ptr)};
                case type::Int64: return {*(float*)this->val_ptr >= static_cast<float>(*(long long*)v.val_ptr)};
                case type::Float: return {*(float*)this->val_ptr >= *(float*)v.val_ptr};
                case type::Double: return {*(float*)this->val_ptr >= *(double*)v.val_ptr};
                case type::String: case type::Boolean:   case type::Typeid: break;
            }
            break;
        case type::Double:
            switch (v.val_type.basic) {
                case type::Int16: return {*(double*)this->val_ptr >= *(int*)v.val_ptr};
                case type::Int32: return {*(double*)this->val_ptr >= *(long*)v.val_ptr};
                case type::Int64: return {*(double*)this->val_ptr >= static_cast<double>(*(long long*)v.val_ptr)};
                case type::Float: return {*(double*)this->val_ptr >= *(float*)v.val_ptr};
                case type::Double: return {*(double*)this->val_ptr >= *(double*)v.val_ptr};
                case type::String: case type::Boolean:   case type::Typeid: break;
            }
            break;
        case type::String:
        case type::Boolean:
         
        case type::Typeid:
            break;
    }
    return {0};
}
Val Val::operator ||(Val v) {
    switch (this->val_type.basic) {
        case type::Boolean:
            return {*(bool*)this->val_ptr || *(bool*)v.val_ptr};
        case type::Int16: case type::Int32: case type::Int64: case type::Float: case type::Double: case type::String:   case type::Typeid: break;
    }
    return {0};
}
Val Val::operator &&(Val v) {
    switch (this->val_type.basic) {
        case type::Boolean:
            return {*(bool*)this->val_ptr && *(bool*)v.val_ptr};
        case type::Int16: case type::Int32: case type::Int64: case type::Float: case type::Double: case type::String:   case type::Typeid: break;
    }
    return {0};
}
Val Val::operator! () {
    switch (this->val_type.basic) {
        case type::Boolean:
            return {!(*(bool*)this->val_ptr)};
        case type::Int16: case type::Int32: case type::Int64: case type::Float: case type::Double: case type::String:   case type::Typeid: break;
    }
    return {0};
}

type::BasicType Val::getBasicType() const { return val_type.basic; }
void* Val::val() { return val_ptr; }
type::UnitType Val::getType() const { return val_type; }
void Val::freeVal() {
    switch (val_type.basic) {
        case type::Int16: delete (int*)val_ptr; break;
        case type::Int32: delete (long*)val_ptr; break;
        case type::Int64: delete (long long*)val_ptr; break;
        case type::Float: delete (float*)val_ptr; break;
        case type::Double: delete (double*)val_ptr; break;
        case type::Boolean: delete (bool*)val_ptr; break;
        case type::String: delete (std::string*)val_ptr; break;
          break;
        case type::Typeid: break;
    }
}
