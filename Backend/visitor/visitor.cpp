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
        case eq: return "eq"; break;
        case neq: return "neq"; break;
        case gt: return "gt"; break;
        case lt: return "lt"; break;
        case ge: return "ge"; break;
        case le: return "le"; break;
        case no: return "no"; break;
        case logic_and: return "logic_and"; break;
        case logic_or: return "logic_or"; break;
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
        case lexer::Boolean:
            if (node.token.content == "true")
                out.emplace_back(CodeKind::push_bool, 1, node.token.line, node.token.column);
            else if (node.token.content == "false")
                out.emplace_back(CodeKind::push_bool, 0, node.token.line, node.token.column);
        case lexer::Keyword: case lexer::Symbol: case lexer::Eof: case lexer::NullToken: break;
            break;
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
void Visitor::visitCompareOp(const parser::Node& node) {
    if (node.token.content == "==")
        out.emplace_back(CodeKind::eq, node.token.line, node.token.column);
    else if (node.token.content == "!=")
        out.emplace_back(CodeKind::neq, node.token.line, node.token.column);
    else if (node.token.content == ">")
        out.emplace_back(CodeKind::gt, node.token.line, node.token.column);
    else if (node.token.content == "<")
        out.emplace_back(CodeKind::lt, node.token.line, node.token.column);
    else if (node.token.content == ">=")
        out.emplace_back(CodeKind::ge, node.token.line, node.token.column);
    else if (node.token.content == "<=")
        out.emplace_back(CodeKind::le, node.token.line, node.token.column);
}
void Visitor::visitCompareExpression(parser::Node node) {
    visitAddExpression(node[Marker::head][0]);
    for (size_t i = 0; i < node[Marker::ops].subs.size(); i ++) {
        visitAddExpression(node[Marker::factors][i]);
        visitCompareOp(node[Marker::ops][i]);
    }
}
void Visitor::visitBooleanOp(const parser::Node& node) {
    if (node.token.content == "&&")
        out.emplace_back(CodeKind::logic_and, node.token.line, node.token.column);
    else if (node.token.content == "||")
        out.emplace_back(CodeKind::logic_or, node.token.line, node.token.column);
    else if (node.token.content == "!")
        out.emplace_back(CodeKind::no, node.token.line, node.token.column);
}
void Visitor::visitBooleanExpression(parser::Node node) {
    visitCompareExpression(node[Marker::head][0]);
    for (size_t i = 0; i < node[Marker::ops].subs.size(); i ++) {
        visitCompareExpression(node[Marker::factors][i]);
        visitBooleanOp(node[Marker::ops][i]);
    }
}