//
// Created by BALL on 2022/12/26.
//

#include "scope.h"

#include <utility>

using namespace storage;

//Scope
Scope::Scope(std::string i): ident(std::move(i)) {}
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
    space.pop_back();
    deepC --;
}
std::string Space::getIdent() {
    return space[deepC].ident;
}

template<typename T>
void Space::createMember(std::string name, T val) {
    space[deepC].members.insert(Member(name, Val(val)));
}

template<typename T>
void Space::createMemberWithType(std::string name, T val, type::Type t) {
    space[deepC].members.insert(Member(name, Val(val, t)));
}

void Space::deleteMember(std::string name) {
    if (space[deepC].members.find(name) != space[deepC].members.end())
        space[deepC].members.erase(name);
    else {
        auto temp = static_cast<int>(deepC);
        while (temp > 0) {
            temp --;
            if (space[static_cast<size_t>(temp)].members.find(name) != space[static_cast<size_t>(temp)].members.end()) {
                space[static_cast<size_t>(temp)].members.erase(name);
                return ;
            }
        }
        // TODO: WILL ERROR
    }
}
bool Space::findMember(std::string name) {
    if (space[deepC].members.find(name) != space[deepC].members.end())
        return true;
    else {
        auto temp = static_cast<int>(deepC);
        while (temp > 0) {
            temp --;
            if (space[static_cast<size_t>(temp)].members.find(name) != space[static_cast<size_t>(temp)].members.end())
                return true;
        }
        return false;
    }
}