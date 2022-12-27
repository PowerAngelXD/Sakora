//
// Created by BALL on 2022/12/22.
//

#include "ast.h"

#include <utility>

parser::Node::Node(NodeKind k): kind(k), subs() {}
parser::Node::Node(lexer::Token tok): token(std::move(tok)), subs() {}
parser::Node::Node(NodeKind k, lexer::Token tok): kind(k), token(std::move(tok)), subs() {}

parser::Node& parser::Node::operator[](size_t index) {
    return this->subs[index];
}
