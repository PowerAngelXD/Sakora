//
// Created by BALL on 2022/12/28.
//

#include "identifier.h"

#include <utility>

storage::Identifier::Identifier(std::string c): Identifier(std::move(c), Modifier::Static, OwnKind::Own) {}
storage::Identifier::Identifier(std::string c, Modifier m, OwnKind o): content(std::move(c)), ownership(o), mod(m) {}

// Get the identifier content
std::string storage::Identifier::ident() { return content; }
std::string storage::Identifier::operator() () { return content; }

bool storage::Identifier::isRef() { return ownership != OwnKind::Own; }
storage::OwnKind storage::Identifier::getRefKind() {
    if (!isRef()) {} // TODO: WILL ERROR

    return ownership;
}
bool storage::Identifier::isDynamic() { return mod == Modifier::Dynamic; }