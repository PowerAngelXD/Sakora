//
// Created by BALL on 2022/12/28.
//

#include "environment.h"

#include <utility>

using namespace sakVM_core;

Environment::Environment(std::vector<std::string> cp, int ln, int col): runtime(), constantPool(std::move(cp)), line(ln), column(col) {}

void Environment::push(storage::Val val) {
    runtime.push(val);
}
storage::Val Environment::peek() { return runtime.top(); }
storage::Val Environment::pop() {
    storage::Val ret = runtime.top();
    runtime.pop();
    return ret;
}

bool Environment::findIdentifier(const std::string& ident) { return space.findMember(ident); }
storage::Val & Environment::getVal(const std::string& ident, int ln, int col) { return space.getVal(ident, ln, col); }
void Environment::deleteVal(const std::string& ident, int ln, int col) { space.deleteMember(ident, ln, col); }

std::string Environment::getConstant(size_t index) { return constantPool[index]; }

template<typename ValType>
void Environment::createValue(std::string ident, ValType val, int ln, int col) { space.createMember(ident, val, ln, col); }

template<typename ValType>
void Environment::createValueWithType(std::string ident, ValType val, type::Type type, int ln, int col) {
    space.createMemberWithType(ident, val, type, ln, col);
}