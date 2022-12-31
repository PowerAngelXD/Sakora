//
// Created by BALL on 2022/12/26.
//

#include "scope.h"

#include <utility>

using namespace storage;

//Scope
Scope::Scope(std::string i): ident(std::move(i)) {}

Val & Scope::getMem(std::string id, int ln, int col) {
    for (auto mem: members) {
        if (get<0>(mem) == id) return get<2>(mem);
    }
    throw storage_error::UnknownIdentifierError(id, ln, col);
}
//


Space::Space() {
    space.emplace_back(std::string("global"));
    deepC = 0;
}

void Space::createScope(std::string i) {
    space.emplace_back(i);
    deepC ++;
}
void Space::addScope(Scope s) {
    space.push_back(s);
    deepC ++;
}
void Space::deleteScope() {
    if (deepC == 0) return;

    space.pop_back();
    deepC --;
}
std::string Space::getIdent() {
    return space[deepC].ident;
}

template<typename T>
void Space::createMember(std::string name, T val, int ln, int col) {
    if (findMember(name)) {
        throw storage_error::DuplicateIdentifierError("", ln, col);
    }
    space[deepC].members.emplace_back(name, Identifier(name), val);
}

template<typename T>
void Space::createMemberWithType(std::string name, T val, type::Type t, int ln, int col) {
    if (findMember(name)) {
        throw storage_error::DuplicateIdentifierError(name, ln, col);
    }
    space[deepC].members.emplace_back(name, Identifier(name), Val(val, t));
}

template<typename T>
void Space::createMemberCompletely(std::string name, Identifier id, T val, type::Type t, int ln, int col) {
    if (findMember(name)) {
        throw storage_error::DuplicateIdentifierError(name, ln, col);
    }
    space[deepC].members.emplace_back(name, id, Val(val, t));
}

void Space::deleteMember(const std::string& name, int ln, int col) {
    for (auto scope: space) {
        for (size_t i = 0; i < scope.members.size(); i ++) {
            auto mem = scope.members[i];
            if (get<0>(mem) == name) scope.members.erase(scope.members.begin() + static_cast<int>(i));
        }
    }
    throw storage_error::UnknownIdentifierError(name, ln, col);
}
Val& Space::getVal(const std::string& name, int ln, int col) {
    for (auto scope: space) {
        for (size_t i = 0; i < scope.members.size(); i ++) {
            auto mem = scope.members[i];
            if (get<0>(mem) == name) return scope.getMem(name);
        }
    }
    throw storage_error::UnknownIdentifierError(name, ln, col);
}
bool Space::findMember(const std::string& name) {
    for (const auto& scope: space) {
        for (auto mem : scope.members) {
            if (get<0>(mem) == name) return true;
        }
    }
    return false;
}