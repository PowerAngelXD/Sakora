//
// Created by BALL on 2022/12/25.
//

#include "visitor.h"

using namespace visitor;
using namespace parser;

std::string visitor::kind_to_string(CodeKind k) {
    switch (k) {
        case push_float: return "push_float";
        case push_double: return "push_double";
        case push_i16: return "push_i16";
        case push_i32: return "push_i32";
        case push_i64: return "push_i64";
        case push_bool: return "push_bool";
        case push_str: return "push_str";
        case push_iden: return "push_iden";
        case add: return "add";
        case sub: return "sub";
        case mul: return "mul";
        case div: return "div";
        case gmem: return "gmem";
        case mod: return "mod";
    }
    return "null code";
}

Code::Code(CodeKind k, int l, int c): kind(k),val(0), ln(l), col(c) {}
Code::Code(CodeKind k, double v, int l, int c): kind(k), val(v), ln(l), col(c) {}

Visitor::Visitor(parser::Node src): source(std::move(src)) {}

void Visitor::visitValToken(const parser::Node& node) {
    switch (node.token.kind) {
        case lexer::Number:
            if (node.token.content.find('.') != std::string::npos) {
                if (node.token.content.size() > 10)
                    out.emplace_back(CodeKind::push_double, std::stod(node.token.content), node.token.line, node.token.column);
                else
                    out.emplace_back(CodeKind::push_float, std::stof(node.token.content), node.token.line, node.token.column);
            }
            else {
                if (node.token.content.size() >= 6)
                    out.emplace_back(CodeKind::push_i64, static_cast<double>(std::stoi(node.token.content)), node.token.line, node.token.column);
                else
                    out.emplace_back(CodeKind::push_i32, static_cast<double>(std::stoi(node.token.content)), node.token.line, node.token.column);
            }
            break;
        case lexer::String:
            constantPool.push_back(node.token.content);
            out.emplace_back(CodeKind::push_str, static_cast<double>(constantPool.size() - 1), node.token.line, node.token.column);
            break;
        case lexer::Ident:
            constantPool.push_back(node.token.content);
            out.emplace_back(CodeKind::push_iden, static_cast<double>(constantPool.size() - 1), node.token.line, node.token.column);
            break;
        case lexer::Keyword: case lexer::Symbol: case lexer::Eof: case lexer::NullToken: break;
    }
}
void Visitor::visitBasicOp(const parser::Node& node) {
    out.emplace_back(CodeKind::gmem, node.token.line, node.token.column);
}
void Visitor::visitBasicExpression(parser::Node node) {
    visitValToken(node[Marker::head][0]);

    for (size_t i = 0; i < node[Marker::ops].subs.size(); i ++) {
        visitValToken(node[Marker::factors][i]);
        visitBasicOp(node[Marker::ops][i]);
    }
}
void Visitor::visitMulOp(const parser::Node& node) {
    if (node.token.content == "*")
        out.emplace_back(CodeKind::mul, node.token.line, node.token.column);
    else if (node.token.content == "/")
        out.emplace_back(CodeKind::div, node.token.line, node.token.column);
    else if (node.token.content == "%")
        out.emplace_back(CodeKind::mod, node.token.line, node.token.column);
}
void Visitor::visitMulExpression(parser::Node node) {
    visitBasicExpression(node[Marker::head][0]);
    for (size_t i = 0; i < node[Marker::ops].subs.size(); i ++) {
        visitBasicExpression(node[Marker::factors][i]);
        visitMulOp(node[Marker::ops][i]);
    }
}
void Visitor::visitAddOp(const Node& node) {
    if (node.token.content == "+")
        out.emplace_back(CodeKind::add, node.token.line, node.token.column);
    else if (node.token.content == "-")
        out.emplace_back(CodeKind::sub, node.token.line, node.token.column);
}
void Visitor::visitAddExpression(parser::Node node) {
    visitMulExpression(node[Marker::head][0]);
    for (size_t i = 0; i < node[Marker::ops].subs.size(); i ++) {
        visitMulExpression(node[Marker::factors][i]);
        visitAddOp(node[Marker::ops][i]);
    }
}