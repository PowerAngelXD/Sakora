//
// Created by BALL on 2022/12/26.
//

#include "value.h"

#include <utility>
#include <sstream>

using namespace storage;

FlagValue::FlagValue(std::string c):content(c) {}

bool storage::doubleEqual(double d1, double d2) {
    return std::abs(d1 - d2) < DBL_EPSILON;
}


Val::Val(long long v) {
    val_size = sizeof(long long);
    val_ptr = (void *) new decltype(v);
    memcpy(val_ptr, &v, val_size);
    val_type = type::UnitType(type::BasicType::Integer);
}
Val::Val(double v) {
    val_size = sizeof(double);
    val_ptr = (void*)new decltype(v);
    memcpy(val_ptr, &v, val_size);
    val_type = type::UnitType(type::BasicType::Decimal);
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
Val::Val(FlagValue v) {
    val_size = sizeof(FlagValue);
    val_ptr = (void*)new FlagValue;
    memcpy(val_ptr, &v, val_size);
    val_type = type::UnitType(type::BasicType::Flag);
}

template<typename T>
Val::Val(T v, type::Type t) {
    val_size = sizeof(T);
    val_ptr = (void*)new decltype(v);
    memcpy(val_ptr, &v, val_size);
    val_type = std::move(t);
}

type::BasicType Val::getBasicType() const {
    if (!val_type.isStructure())
        return val_type.head.unit_type->basic;
    else {
        throw "fff";
    }
}
type::Type Val::getType() const { return val_type; }
void Val::setLnCol(int ln, int col) {
    line = ln;
    column = col;
}
void* Val::val() { return val_ptr; }

void Val::freeVal() {

}

Val Val::operator+ (Val v) {
    if (this->val_type.isStructure())
        throw storage_error::UnsupportedOperationError(storage_error::structure_mode, line, column);

    switch (this->val_type.head.unit_type->basic) {
        case type::Integer: {
            switch (v.val_type.head.unit_type->basic) {
                case type::Integer: return {INT(this->val_ptr) + INT(v.val_ptr)};
                case type::Decimal: return {static_cast<double>(INT(this->val_ptr)) + DECI(v.val_ptr)};
                default:
                    throw storage_error::UnsupportedOperationError("+@Integer@" + v.val_type.head.unit_type->to_string(), line, column);
            }
        }
        case type::Decimal: {
            switch (v.val_type.head.unit_type->basic) {
                case type::Integer: return {DECI(this->val_ptr) + static_cast<double>(INT(v.val_ptr))};
                case type::Decimal: return {DECI(this->val_ptr) + DECI(v.val_ptr)};
                default:
                    throw storage_error::UnsupportedOperationError("+@Integer@" + v.val_type.head.unit_type->to_string(), line, column);
            }
        }
        default:
            throw storage_error::UnsupportedOperationError("+@" + this->val_type.head.unit_type->to_string() + "@" + v.val_type.head.unit_type->to_string(), line, column);
    }
}
Val Val::operator- (Val v) {
    if (this->val_type.isStructure())
        throw storage_error::UnsupportedOperationError(storage_error::structure_mode, line, column);

    switch (this->val_type.head.unit_type->basic) {
        case type::Integer: {
            switch (v.val_type.head.unit_type->basic) {
                case type::Integer: return {INT(this->val_ptr) - INT(v.val_ptr)};
                case type::Decimal: return {static_cast<double>(INT(this->val_ptr)) - DECI(v.val_ptr)};
                default:
                    throw storage_error::UnsupportedOperationError("-@Integer@" + v.val_type.head.unit_type->to_string(), line, column);
            }
        }
        case type::Decimal: {
            switch (v.val_type.head.unit_type->basic) {
                case type::Integer: return {DECI(this->val_ptr) - static_cast<double>(INT(v.val_ptr))};
                case type::Decimal: return {DECI(this->val_ptr) - DECI(v.val_ptr)};
                default:
                    throw storage_error::UnsupportedOperationError("-@Decimal@" + v.val_type.head.unit_type->to_string(), line, column);
            }
        }
        default:
            throw storage_error::UnsupportedOperationError("-@" + this->val_type.head.unit_type->to_string() + "@" + v.val_type.head.unit_type->to_string(), line, column);
    }
}
Val Val::operator* (Val v) {
    if (this->val_type.isStructure())
        throw storage_error::UnsupportedOperationError(storage_error::structure_mode, line, column);

    switch (this->val_type.head.unit_type->basic) {
        case type::Integer: {
            switch (v.val_type.head.unit_type->basic) {
                case type::Integer: return {INT(this->val_ptr) * INT(v.val_ptr)};
                case type::Decimal: return {static_cast<double>(INT(this->val_ptr)) * DECI(v.val_ptr)};
                default:
                    throw storage_error::UnsupportedOperationError("*@Integer@" + v.val_type.head.unit_type->to_string(), line, column);
            }
        }
        case type::Decimal: {
            switch (v.val_type.head.unit_type->basic) {
                case type::Integer: return {DECI(this->val_ptr) * static_cast<double>(INT(v.val_ptr))};
                case type::Decimal: return {DECI(this->val_ptr) * DECI(v.val_ptr)};
                default:
                    throw storage_error::UnsupportedOperationError("*@Decimal@" + v.val_type.head.unit_type->to_string(), line, column);
            }
        }
        default:
            throw storage_error::UnsupportedOperationError("*@" + this->val_type.head.unit_type->to_string() + "@" + v.val_type.head.unit_type->to_string(), line, column);
    }
}
Val Val::operator/ (Val v) {
    if (this->val_type.isStructure())
        throw storage_error::UnsupportedOperationError(storage_error::structure_mode, line, column);

    switch (this->val_type.head.unit_type->basic) {
        case type::Integer: {
            switch (v.val_type.head.unit_type->basic) {
                case type::Integer: {
                    return {(double)INT(this->val_ptr) / (double)INT(v.val_ptr)};
                }
                case type::Decimal: return {static_cast<double>(INT(this->val_ptr)) / DECI(v.val_ptr)};
                default:
                    throw storage_error::UnsupportedOperationError("/@Integer@" + v.val_type.head.unit_type->to_string(), line, column);
            }
        }
        case type::Decimal: {
            switch (v.val_type.head.unit_type->basic) {
                case type::Integer: return {DECI(this->val_ptr) / static_cast<double>(INT(v.val_ptr))};
                case type::Decimal: return {DECI(this->val_ptr) / DECI(v.val_ptr)};
                default:
                    throw storage_error::UnsupportedOperationError("/@Decimal@" + v.val_type.head.unit_type->to_string(), line, column);
            }
        }
        default:
            throw storage_error::UnsupportedOperationError("/@" + this->val_type.head.unit_type->to_string() + "@" + v.val_type.head.unit_type->to_string(), line, column);
    }
}
Val Val::operator% (Val v) {
    if (this->val_type.isStructure())
        throw storage_error::UnsupportedOperationError(storage_error::structure_mode, line, column);

    switch (this->val_type.head.unit_type->basic) {
        case type::Integer: {
            switch (v.val_type.head.unit_type->basic) {
                case type::Integer: return {INT(this->val_ptr) % INT(v.val_ptr)};
                default:
                    throw storage_error::UnsupportedOperationError("%@Integer@" + v.val_type.head.unit_type->to_string(), line, column);
            }
        }
        default:
            throw storage_error::UnsupportedOperationError("%@" + this->val_type.head.unit_type->to_string() + "@" + v.val_type.head.unit_type->to_string(), line, column);
    }
}
Val Val::operator== (Val v) {
    if (this->val_type.isStructure())
        throw storage_error::UnsupportedOperationError(storage_error::structure_mode, line, column);

    switch (this->val_type.head.unit_type->basic) {
        case type::Integer: {
            switch (v.val_type.head.unit_type->basic) {
                case type::Integer:
                    return {INT(this->val_ptr) == INT(v.val_ptr)};
                default:
                    throw storage_error::UnsupportedOperationError(storage_error::type_equal_mode, line, column);
            }
        }
        case type::Decimal: {
            switch (v.val_type.head.unit_type->basic) {
                case type::Decimal:
                    return {doubleEqual(DECI(this->val_ptr), DECI(v.val_ptr))};
                default:
                    throw storage_error::UnsupportedOperationError(storage_error::type_equal_mode, line, column);
            }
        }
        case type::Boolean: {
            switch (v.val_type.head.unit_type->basic) {
                case type::Boolean:
                    return {BOOL(this->val_ptr) == BOOL(v.val_ptr)};
                default:
                    throw storage_error::UnsupportedOperationError(storage_error::type_equal_mode, line, column);
            }
        }
        case type::String: {
            switch (v.val_type.head.unit_type->basic) {
                case type::String:
                    return {STR(this->val_ptr) == STR(v.val_ptr)};
                default:
                    throw storage_error::UnsupportedOperationError(storage_error::type_equal_mode, line, column);
            }
        }
        case type::Typeid: {
            switch (v.val_type.head.unit_type->basic) {
                case type::Typeid:
                    return {TYPEID(this->val_ptr) == TYPEID(v.val_ptr)};
                default:
                    throw storage_error::UnsupportedOperationError(storage_error::type_equal_mode, line, column);
            }
        }
        default:
            throw storage_error::UnsupportedOperationError(storage_error::type_equal_mode, line, column);
    }
}
Val Val::operator!= (Val v) {
    if (this->val_type.isStructure())
        throw storage_error::UnsupportedOperationError(storage_error::structure_mode, line, column);

    switch (this->val_type.head.unit_type->basic) {
        case type::Integer: {
            switch (v.val_type.head.unit_type->basic) {
                case type::Integer:
                    return {INT(this->val_ptr) != INT(v.val_ptr)};
                default:
                    throw storage_error::UnsupportedOperationError(storage_error::type_equal_mode, line, column);
            }
        }
        case type::Decimal: {
            switch (v.val_type.head.unit_type->basic) {
                case type::Decimal:
                    return {!doubleEqual(DECI(this->val_ptr), DECI(v.val_ptr))};
                default:
                    throw storage_error::UnsupportedOperationError(storage_error::type_equal_mode, line, column);
            }
        }
        case type::Boolean: {
            switch (v.val_type.head.unit_type->basic) {
                case type::Boolean:
                    return {BOOL(this->val_ptr) != BOOL(v.val_ptr)};
                default:
                    throw storage_error::UnsupportedOperationError(storage_error::type_equal_mode, line, column);
            }
        }
        case type::String: {
            switch (v.val_type.head.unit_type->basic) {
                case type::String:
                    return {STR(this->val_ptr) != STR(v.val_ptr)};
                default:
                    throw storage_error::UnsupportedOperationError(storage_error::type_equal_mode, line, column);
            }
        }
        case type::Typeid: {
            switch (v.val_type.head.unit_type->basic) {
                case type::Typeid:
                    return {TYPEID(this->val_ptr) != TYPEID(v.val_ptr)};
                default:
                    throw storage_error::UnsupportedOperationError(storage_error::type_equal_mode, line, column);
            }
        }
        default:
            throw storage_error::UnsupportedOperationError(storage_error::type_equal_mode, line, column);
    }
}
Val Val::operator< (Val v) {
    if (this->val_type.isStructure())
        throw storage_error::UnsupportedOperationError(storage_error::structure_mode, line, column);

    switch (this->val_type.head.unit_type->basic) {
        case type::Integer: {
            switch (v.val_type.head.unit_type->basic) {
                case type::Integer: return {INT(this->val_ptr) < INT(v.val_ptr)};
                case type::Decimal: return {static_cast<double>(INT(this->val_ptr)) < DECI(v.val_ptr)};
                default:
                    throw storage_error::UnsupportedOperationError("<@Integer@" + v.val_type.head.unit_type->to_string(), line, column);
            }
        }
        case type::Decimal: {
            switch (v.val_type.head.unit_type->basic) {
                case type::Integer: return {DECI(this->val_ptr) < static_cast<double>(INT(v.val_ptr))};
                case type::Decimal: return {DECI(this->val_ptr) < DECI(v.val_ptr)};
                default:
                    throw storage_error::UnsupportedOperationError("<@Decimal@" + v.val_type.head.unit_type->to_string(), line, column);
            }
        }
        default:
            throw storage_error::UnsupportedOperationError("<@" + this->val_type.head.unit_type->to_string() + "@" + v.val_type.head.unit_type->to_string(), line, column);
    }
}
Val Val::operator> (Val v) {
    if (this->val_type.isStructure())
        throw storage_error::UnsupportedOperationError(storage_error::structure_mode, line, column);

    switch (this->val_type.head.unit_type->basic) {
        case type::Integer: {
            switch (v.val_type.head.unit_type->basic) {
                case type::Integer: return {INT(this->val_ptr) > INT(v.val_ptr)};
                case type::Decimal: return {static_cast<double>(INT(this->val_ptr)) > DECI(v.val_ptr)};
                default:
                    throw storage_error::UnsupportedOperationError(">@Integer@" + v.val_type.head.unit_type->to_string(), line, column);
            }
        }
        case type::Decimal: {
            switch (v.val_type.head.unit_type->basic) {
                case type::Integer: return {DECI(this->val_ptr) > static_cast<double>(INT(v.val_ptr))};
                case type::Decimal: return {DECI(this->val_ptr) > DECI(v.val_ptr)};
                default:
                    throw storage_error::UnsupportedOperationError(">@Decimal@" + v.val_type.head.unit_type->to_string(), line, column);
            }
        }
        default:
            throw storage_error::UnsupportedOperationError(">@" + this->val_type.head.unit_type->to_string() + "@" + v.val_type.head.unit_type->to_string(), line, column);
    }
}
Val Val::operator<= (Val v) {
    if (this->val_type.isStructure())
        throw storage_error::UnsupportedOperationError(storage_error::structure_mode, line, column);

    switch (this->val_type.head.unit_type->basic) {
        case type::Integer: {
            switch (v.val_type.head.unit_type->basic) {
                case type::Integer: return {INT(this->val_ptr) <= INT(v.val_ptr)};
                case type::Decimal: return {static_cast<double>(INT(this->val_ptr)) <= DECI(v.val_ptr)};
                default:
                    throw storage_error::UnsupportedOperationError("<=@Integer@" + v.val_type.head.unit_type->to_string(), line, column);
            }
        }
        case type::Decimal: {
            switch (v.val_type.head.unit_type->basic) {
                case type::Integer: return {DECI(this->val_ptr) <= static_cast<double>(INT(v.val_ptr))};
                case type::Decimal: return {DECI(this->val_ptr) <= DECI(v.val_ptr)};
                default:
                    throw storage_error::UnsupportedOperationError("<=@Decimal@" + v.val_type.head.unit_type->to_string(), line, column);
            }
        }
        default:
            throw storage_error::UnsupportedOperationError("<=@" + this->val_type.head.unit_type->to_string() + "@" + v.val_type.head.unit_type->to_string(), line, column);
    }
}
Val Val::operator>= (Val v) {
    if (this->val_type.isStructure())
        throw storage_error::UnsupportedOperationError(storage_error::structure_mode, line, column);

    switch (this->val_type.head.unit_type->basic) {
        case type::Integer: {
            switch (v.val_type.head.unit_type->basic) {
                case type::Integer: return {INT(this->val_ptr) >= INT(v.val_ptr)};
                case type::Decimal: return {static_cast<double>(INT(this->val_ptr)) >= DECI(v.val_ptr)};
                default:
                    throw storage_error::UnsupportedOperationError(">=@Integer@" + v.val_type.head.unit_type->to_string(), line, column);
            }
        }
        case type::Decimal: {
            switch (v.val_type.head.unit_type->basic) {
                case type::Integer: return {DECI(this->val_ptr) >= static_cast<double>(INT(v.val_ptr))};
                case type::Decimal: return {DECI(this->val_ptr) >= DECI(v.val_ptr)};
                default:
                    throw storage_error::UnsupportedOperationError(">=@Decimal@" + v.val_type.head.unit_type->to_string(), line, column);
            }
        }
        default:
            throw storage_error::UnsupportedOperationError(">=@" + this->val_type.head.unit_type->to_string() + "@" + v.val_type.head.unit_type->to_string(), line, column);
    }
}
Val Val::operator ||(Val v) {
    if (this->val_type.isStructure())
        throw storage_error::UnsupportedOperationError(storage_error::structure_mode, line, column);

    switch (this->val_type.head.unit_type->basic) {
        case type::Boolean: {
            switch (v.val_type.head.unit_type->basic) {
                case type::Boolean: return {BOOL(this->val_ptr) || BOOL(v.val_ptr)};
                default:
                    throw storage_error::UnsupportedOperationError("||@Boolean@" + v.val_type.head.unit_type->to_string(), line, column);
            }
        }
        default:
            throw storage_error::UnsupportedOperationError("||@" + this->val_type.head.unit_type->to_string() + "@" + v.val_type.head.unit_type->to_string(), line, column);
    }
}
Val Val::operator &&(Val v) {
    if (this->val_type.isStructure())
        throw storage_error::UnsupportedOperationError(storage_error::structure_mode, line, column);

    switch (this->val_type.head.unit_type->basic) {
        case type::Boolean: {
            switch (v.val_type.head.unit_type->basic) {
                case type::Boolean: return {BOOL(this->val_ptr) && BOOL(v.val_ptr)};
                default:
                    throw storage_error::UnsupportedOperationError("&&@Boolean@" + v.val_type.head.unit_type->to_string(), line, column);
            }
        }
        default:
            throw storage_error::UnsupportedOperationError("&&@" + this->val_type.head.unit_type->to_string() + "@" + v.val_type.head.unit_type->to_string(), line, column);
    }
}
Val Val::operator! () {
    if (this->val_type.isStructure())
        throw storage_error::UnsupportedOperationError(storage_error::structure_mode, line, column);

    switch (this->val_type.head.unit_type->basic) {
        case type::Boolean: {
            return {!BOOL(this->val_ptr)};
        }
        default:
            throw storage_error::UnsupportedOperationError("!@" + this->val_type.head.unit_type->to_string(), line, column);
    }
}

void Val::print() {
    if (this->val_type.isStructure())
        throw storage_error::UnsupportedOperationError(storage_error::structure_mode, line, column);

    switch (this->val_type.head.unit_type->basic) {
        case type::Integer:
            std::cout<<INT(this->val_ptr)<<std::endl;
            break;
        case type::Decimal:
            std::cout<<DECI(this->val_ptr)<<std::endl;
            break;
        case type::Boolean:
            std::cout<<std::boolalpha<<BOOL(this->val_ptr)<<std::noboolalpha<<std::endl;
            break;
        case type::String:
            std::cout<<STR(this->val_ptr)<<std::endl;
            break;
        case type::Typeid:
            std::cout<<"Typeid"<<std::endl;
            break;
        case type::Flag:
            std::cout<<"Flag"<<std::endl;
            break;
    }
}
