//
// Created by BALL on 2022/12/31.
//

#include "sakvm.h"

#include <utility>

// VM
saKVM::saKVM(std::vector<std::string> cp, int ln, int col): env(std::move(cp), ln, col) {};

void saKVM::init(std::vector<std::string> cp, int ln, int col) {
    env = sakVM_core::Environment(std::move(cp), ln, col);
}

void saKVM::run(size_t layer) {
    auto cur_queue = threads[layer];
    for (auto code: cur_queue) {
        switch (code.kind) {
            case visitor::push_int: ins_push_int(code); break;
            case visitor::push_deci: ins_push_deci(code); break;
            case visitor::push_bool: ins_push_bool(code); break;
            case visitor::push_str: ins_push_str(code); break;
            case visitor::push_iden: ins_push_iden(code); break;
            case visitor::add: ins_add(); break;
            case visitor::sub: ins_sub(); break;
            case visitor::mul: ins_mul(); break;
            case visitor::div: ins_div(); break;
            case visitor::gmem: ins_gmem(); break;
            case visitor::mod: ins_mod(); break;
            case visitor::eq: ins_eq(); break;
            case visitor::neq: ins_neq(); break;
            case visitor::gt: ins_gt(); break;
            case visitor::lt: ins_lt(); break;
            case visitor::ge: ins_ge(); break;
            case visitor::le: ins_le(); break;
            case visitor::logic_not: ins_no(); break;
            case visitor::logic_and: ins_logic_and(); break;
            case visitor::logic_or: ins_logic_or(); break;
            case visitor::type_bool:
                break;
            case visitor::type_str:
                break;
            case visitor::type_typeid:
                break;
            case visitor::set_list: ins_set_list(); break;
            case visitor::set_struct_array:
                break;
            case visitor::set_ref:
                break;
            case visitor::set_tuple:
                break;
            case visitor::set_struct:
                break;
            case visitor::type_int:
                break;
            case visitor::type_deci:
                break;
            case visitor::push_flag: ins_push_flag(code); break;
            case visitor::set_mutable_list: ins_set_mutable_list(); break;
            case visitor::stfop: ins_stfop(code); break;
            case visitor::set_fn_type:
                break;
        }
    }
}

// Code set
void saKVM::ins_push_int(visitor::Code code) { env.push(static_cast<long long>(code.val)); }
void saKVM::ins_push_deci(visitor::Code code) { env.push(static_cast<double>(code.val)); }
void saKVM::ins_push_bool(visitor::Code code) { env.push(static_cast<bool>(float_equ(code.val, code.val)))); }
void saKVM::ins_push_str(visitor::Code code) {
    auto str = env.getConstant(static_cast<size_t>(static_cast<int>(code.val)));
    env.push(str);
}
void saKVM::ins_push_flag(visitor::Code code) {
    env.push(visitor::FlagValue((visitor::FlagKind)code.val));
}
void saKVM::ins_push_iden(visitor::Code code) {
    env.push( "<Identifier: " + env.getConstant((size_t)(int)code.val) + ">");
}
void saKVM::ins_set_list() {
    std::vector<storage::Val> list;
    storage::Val head;
    while (true) {
        if (env.peek().getHeadType()->basic == type::Flag) {
            if (env.peek().flag_val().kind == visitor::ArrayEnd)
                break;
        }

        list.push_back(env.pop());
        head = list[0];

        if ((env.peek().getHeadType()->basic != head.getHeadType()->basic) &&
            env.peek().getHeadType()->basic != type::Flag)
            throw storage_error::IllegalTypeDescriptionError(storage_error::diftypes_in_list, 0, 0);
    }
    auto flag = env.pop();
    std::reverse(list.begin(), list.end());
    env.push(list);
}
void saKVM::ins_set_mutable_list() {
    std::vector<storage::Val> list;
    storage::Val head;
    while (true) {
        if (env.peek().getHeadType()->basic == type::Flag) {
            if (env.peek().flag_val().kind == visitor::ArrayEnd)
                break;
        }

        list.push_back(env.pop());
        head = list[0];

        if ((env.peek().getHeadType()->basic != head.getHeadType()->basic) &&
            env.peek().getHeadType()->basic != type::Flag)
            throw storage_error::IllegalTypeDescriptionError(storage_error::diftypes_in_list, 0, 0);
    }
    auto flag = env.pop();
    std::reverse(list.begin(), list.end());
    env.push(storage::Val(list, true));
}
void saKVM::ins_add() {
    auto right = env.pop();
    auto left = env.pop();
    env.push(left + right);
}
void saKVM::ins_sub() {
    auto right = env.pop();
    auto left = env.pop();
    env.push(left - right);
}
void saKVM::ins_mul() {
    auto right = env.pop();
    auto left = env.pop();
    env.push(left * right);
}
void saKVM::ins_div() {
    auto right = env.pop();
    auto left = env.pop();
    env.push(left / right);
}
void saKVM::ins_mod() {
    auto right = env.pop();
    auto left = env.pop();
    env.push(left % right);
}
void saKVM::ins_gt() {
    auto right = env.pop(), left = env.pop();
    env.push(left > right);
}
void saKVM::ins_lt() {
    auto right = env.pop(), left = env.pop();
    env.push(left < right);
}
void saKVM::ins_ge() {
    auto right = env.pop(), left = env.pop();
    env.push(left >= right);
}
void saKVM::ins_le() {
    auto right = env.pop(), left = env.pop();
    env.push(left <= right);
}
void saKVM::ins_eq() {
    auto right = env.pop(), left = env.pop();
    env.push(left == right);
}
void saKVM::ins_neq() {
    auto right = env.pop(), left = env.pop();
    env.push(left != right);
}
void saKVM::ins_logic_or() {
    auto right = env.pop(), left = env.pop();
    env.push(left || right);
}
void saKVM::ins_logic_and() {
    auto right = env.pop(), left = env.pop();
    env.push(left && right);
}
void saKVM::ins_no() {
    auto left = env.pop();
    env.push(!left);
}
void saKVM::ins_gmem() {

}

void saKVM::ins_stfop(visitor::Code code) {
    std::vector<storage::Val> args;
    while (true) {
        if (env.peek().getType().head.unit_type != nullptr) {
            if (env.peek().getHeadType()->basic == type::Flag) {
                if (env.peek().flag_val().kind == visitor::ArrayEnd)
                    break;
            }
        }
        args.push_back(env.pop());
    }
    auto flag = env.pop();
    std::reverse(args.begin(), args.end());

    if (args.size() > 1)
        throw parser_error::SyntaxError("Too many parameters for this operation", 1, 1);

    auto stf = env.getConstant(static_cast<size_t>(static_cast<int>(code.val)));
    if (stf == "typeof") {
        env.push(args[0].getType().to_string());
    }
}
