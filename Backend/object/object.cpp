//
// Created by BALL on 2022/12/27.
//

#include "object.h"

#include <utility>

using namespace type;

// Function Object
FunctionObject::FunctionObject(std::string ident, std::vector<visitor::Code> cq, type::Type ret):
    ident(std::move(ident)), codeQueue(std::move(cq)), retType(ret) {}

type::Type FunctionObject::getReturnType() { return retType; }
Arg FunctionObject::getArg(const std::string& argName) { return {argName, args[argName]}; }

Arg FunctionObject::operator[] (const std::string& argName) { return {argName, args[argName]}; }

std::string FunctionObject::getIdentifier() { return ident; }

// Struct Object
StructObject::StructObject(std::string ident, std::map<std::string, storage::Val> mems): ident(std::move(ident)), members(std::move(mems)) {}

storage::Val StructObject::getMemberVal(const std::string& memIdent) { return members[memIdent]; }
ImplementObject* StructObject::getAssocImpl(const std::string& impl) { return impls[impl]; }
void StructObject::AddImplement(ImplementObject* impl) {}

storage::Val StructObject::operator[] (std::string memIdent) { return members[memIdent]; }
ImplementObject* StructObject::operator() (std::string impl) { return impls[impl]; }

// Implement Object
ImplementObject::ImplementObject(std::string ident): ident(std::move(ident)) {}
ImplementObject::ImplementObject(std::string ident, StructObject* f): ident(std::move(ident)), father(f) {}

void ImplementObject::addMethod(FunctionObject fn) { methods.insert({fn.getIdentifier(), fn}); }
FunctionObject ImplementObject::getMethod(const std::string& methodName) { return methods[methodName]; }
StructObject* ImplementObject::getFather() { return father; }

FunctionObject ImplementObject::operator[] (const std::string& methodName) { return methods[methodName]; }
void ImplementObject::operator+= (FunctionObject fn) { methods.insert({fn.getIdentifier(), fn}); }

// Object
Object::Object(std::string ident, std::vector<visitor::Code> cs, type::Type ret): fnObj(new FunctionObject(std::move(ident), std::move(cs), ret)) {}
Object::Object(std::string ident, std::map<std::string, storage::Val> mems): structObj(new StructObject(std::move(ident), std::move(mems))) {}
Object::Object(std::string ident, StructObject* f): implObj(new ImplementObject(std::move(ident), f)) {}
Object::Object(std::string ident): implObj(new ImplementObject(std::move(ident))) {}