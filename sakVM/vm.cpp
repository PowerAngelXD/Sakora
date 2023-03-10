//
// Created by BALL on 2022/12/31.
//

#include "vm.h"

#include <utility>

// VM
sakVM::sakVM(std::vector<std::string> cp, int ln, int col): env(std::move(cp), ln, col) {};

void sakVM::vm_init(std::vector<std::string> cp, int ln, int col) {
    env = sakVM_core::Environment(std::move(cp), ln, col);
}

void sakVM::vm_run(size_t layer) {
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
            case visitor::set_list:
                break;
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
            case visitor::push_flag:
                break;
            case visitor::set_mutable_list:
                break;
        }
    }
}

// Code set
void sakVM::ins_push_int(visitor::Code code) { env.push(static_cast<long long>(code.val)); }
void sakVM::ins_push_deci(visitor::Code code) { env.push(static_cast<double>(code.val)); }
void sakVM::ins_push_bool(visitor::Code code) { env.push(static_cast<bool>(float_equ(code.val, code.val)))); }
void sakVM::ins_push_str(visitor::Code code) {
    auto str = env.getConstant(static_cast<size_t>(static_cast<int>(code.val)));
    env.push(str);
}
void sakVM::ins_push_iden(visitor::Code code) {
    std::cout<<code.val<<std::endl;
}
void sakVM::ins_add() {
    auto right = env.pop();
    auto left = env.pop();
    env.push(left + right);
}
void sakVM::ins_sub() {
    auto right = env.pop();
    auto left = env.pop();
    env.push(left - right);
}
void sakVM::ins_mul() {
    auto right = env.pop();
    auto left = env.pop();
    env.push(left * right);
}
void sakVM::ins_div() {
    auto right = env.pop();
    auto left = env.pop();
    env.push(left / right);
}
void sakVM::ins_mod() {
    auto right = env.pop();
    auto left = env.pop();
    env.push(left % right);
}
void sakVM::ins_gt() {
    auto right = env.pop(), left = env.pop();
    env.push(left > right);
}
void sakVM::ins_lt() {
    auto right = env.pop(), left = env.pop();
    env.push(left < right);
}
void sakVM::ins_ge() {
    auto right = env.pop(), left = env.pop();
    env.push(left >= right);
}
void sakVM::ins_le() {
    auto right = env.pop(), left = env.pop();
    env.push(left <= right);
}
void sakVM::ins_eq() {
    auto right = env.pop(), left = env.pop();
    env.push(left == right);
}
void sakVM::ins_neq() {
    auto right = env.pop(), left = env.pop();
    env.push(left != right);
}
void sakVM::ins_logic_or() {
    auto right = env.pop(), left = env.pop();
    env.push(left || right);
}
void sakVM::ins_logic_and() {
    auto right = env.pop(), left = env.pop();
    env.push(left && right);
}
void sakVM::ins_no() {
    auto left = env.pop();
    env.push(!left);
}
void sakVM::ins_gmem() {

}