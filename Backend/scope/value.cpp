//
// Created by BALL on 2022/12/26.
//

#include "value.h"

#include <utility>
#include <sstream>

using namespace storage;

bool storage::doubleEqual(double d1, double d2) {
    return std::abs(d1 - d2) < DBL_EPSILON;
}

Val::Val(std::vector<Val> list) {
    val_size = sizeof(std::vector<Val>);
    val_ptr = new std::vector<Val>;
    *(std::vector<Val>*)val_ptr = list;

    type::Type t = {type::optBuilder(type::Array)};
    for(const auto & i : list) {
        t.type_content.push_back(type::optBuilder(i.getHeadType()->basic));
    }

    val_type = t;
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
Val::Val(visitor::FlagValue v) {
    val_size = sizeof(visitor::FlagValue);
    val_ptr = (void*)new visitor::FlagValue;
    memcpy(val_ptr, &v, val_size);
    val_type = type::UnitType(type::BasicType::Flag);
}

template<typename T>
Val::Val(T v, type::Type t) {
    val_size = sizeof(decltype(v));
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
void* Val::get_ptr() { return val_ptr; }

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

void Val::print(bool is_repr) {
    if (this->val_type.isStructure()) {
        switch (*this->val_type.head.s_kind) {
            case type::Struct:
                break;
            case type::Array: {
                std::cout<<"[";
                for (size_t i = 0; i < this->val_type.type_content.size() - 1; i ++) {
                    (*(std::vector<Val>*)this->val_ptr)[i].print(true);
                    if (i == this->val_type.type_content.size() - 2) {}
                    else
                        std::cout<<",";
                }
                std::cout<<"]"<<std::endl;
                return;
            }
            case type::VarArray:
                break;
            case type::Impl:
                break;
            case type::Fn:
                break;
        }
    }

    switch (this->val_type.head.unit_type->basic) {
        case type::Integer:
            if (is_repr)
                std::cout<<INT(this->val_ptr);
            else
                std::cout<<INT(this->val_ptr)<<std::endl;
            break;
        case type::Decimal:
            if (is_repr)
                std::cout<<DECI(this->val_ptr);
            else
                std::cout<<DECI(this->val_ptr)<<std::endl;
            break;
        case type::Boolean:
            if (is_repr)
                std::cout<<std::boolalpha<<BOOL(this->val_ptr)<<std::noboolalpha;
            else
                std::cout<<std::boolalpha<<BOOL(this->val_ptr)<<std::noboolalpha<<std::endl;
            break;
        case type::String:
            if (is_repr)
                std::cout<<STR(this->val_ptr);
            else
                std::cout<<"\""<<STR(this->val_ptr)<<"\""<<std::endl;
            break;
        case type::Typeid:
            if (is_repr)
                std::cout<<"Typeid";
            else
                std::cout<<"Typeid"<<std::endl;
            break;
        case type::Flag:
            std::cout<<"Flag"<<std::endl;
            break;
    }
}

long long Val::int_val() {
    if (this->getHeadType()->basic != type::Integer)
        throw storage_error::UnsupportedOperationError(storage_error::get_chosen_type_val_mode, -1, -1);

    return INT(val_ptr);
}

double Val::deci_val() {
    if (this->getHeadType()->basic != type::Decimal)
        throw storage_error::UnsupportedOperationError(storage_error::get_chosen_type_val_mode, -1, -1);

    return DECI(val_ptr);
}

std::string Val::str_val() {
    if (this->getHeadType()->basic != type::String)
        throw storage_error::UnsupportedOperationError(storage_error::get_chosen_type_val_mode, -1, -1);

    return STR(val_ptr);
}

bool Val::bool_val() {
    if (this->getHeadType()->basic != type::Boolean)
        throw storage_error::UnsupportedOperationError(storage_error::get_chosen_type_val_mode, -1, -1);

    return BOOL(val_ptr);
}

visitor::FlagValue Val::flag_val() {
    if (this->getHeadType()->basic != type::Flag)
        throw storage_error::UnsupportedOperationError(storage_error::get_chosen_type_val_mode, -1, -1);

    return FLAG(val_ptr);
}

type::Type Val::valtype_val() {
    if (this->getHeadType()->basic != type::Typeid)
        throw storage_error::UnsupportedOperationError(storage_error::get_chosen_type_val_mode, -1, -1);

    return TYPEID(val_ptr);
}

bool Val::is_null() {
    return val_ptr == nullptr;
}

type::UnitType* Val::getHeadType() const {
    return val_type.head.unit_type;
}
