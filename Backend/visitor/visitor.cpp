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
        case logic_not: return "no"; break;
        case logic_and: return "logic_and"; break;
        case logic_or: return "logic_or"; break;
    }
    return "null code";
}

Code::Code(CodeKind k, int l, int c): kind(k),val(0), ln(l), col(c) {}
Code::Code(CodeKind k, double v, int l, int c): kind(k), val(v), ln(l), col(c) {}

void Visitor::visitValToken(parser::TokenNode* node) {
    switch (node->token->kind) {
        case lexer::Number:
            if (node->token->content.find('.') != std::string::npos) {
                if (node->token->content.size() > 10)
                    out.emplace_back(CodeKind::push_double, std::stod(node->token->content), node->token->line, node->token->column);
                else
                    out.emplace_back(CodeKind::push_float, std::stof(node->token->content), node->token->line, node->token->column);
            }
            else {
                if (node->token->content.size() >= 6)
                    out.emplace_back(CodeKind::push_i64, static_cast<double>(std::stoi(node->token->content)), node->token->line, node->token->column);
                else
                    out.emplace_back(CodeKind::push_i32, static_cast<double>(std::stoi(node->token->content)), node->token->line, node->token->column);
            }
            break;
        case lexer::String:
            constantPool.push_back(node->token->content);
            out.emplace_back(CodeKind::push_str, static_cast<double>(constantPool.size() - 1), node->token->line, node->token->column);
            break;
        case lexer::Ident:
            constantPool.push_back(node->token->content);
            out.emplace_back(CodeKind::push_iden, static_cast<double>(constantPool.size() - 1), node->token->line, node->token->column);
            break;
        case lexer::Boolean:
            if (node->token->content == "true")
                out.emplace_back(CodeKind::push_bool, 1, node->token->line, node->token->column);
            else if (node->token->content == "false")
                out.emplace_back(CodeKind::push_bool, 0, node->token->line, node->token->column);
        case lexer::Keyword: case lexer::Symbol: case lexer::Eof: case lexer::NullToken: break;
            break;
    }
}

void Visitor::visitBasicOp(parser::BasicExprNode::CallingOpOption* node) {
    if (node->call_op != nullptr) {

    }
    else if (node->call_op != nullptr) {

    }
    // TODO
}
void Visitor::visitBasicExpression(parser::BasicExprNode* node) {
    visitValToken(node->factor);
    for (size_t i = 0; i < node->ops->size(); i ++) {
        visitBasicOp(node->ops->at(i));
    }
}
void Visitor::visitPrimOp(parser::TokenNode* node) {
    out.push_back(Code {CodeKind::gmem, node->token->line, node->token->column});
}
void Visitor::visitPrimExpression(parser::PrimaryExprNode* node) {
    visitBasicExpression(node->head->head);
    for (size_t i = 0; i < node->ops->size(); i ++) {
        visitPrimOp(node->ops->at(i)->op);
        visitBasicExpression(node->factors->at(i)->head);
    }
}
void Visitor::visitMulOp(parser::MulExprNode::MulOpOption* node) {

}
void Visitor::visitMulExpression(parser::MulExprNode* node) {

}
void Visitor::visitAddOp(parser::AddExprNode::AddOpOption* node) {

}
void Visitor::visitAddExpression(parser::AddExprNode* node) {

}
void Visitor::visitCompareOp(parser::CompareExprNode::CompareOpOption* node) {

}
void Visitor::visitCompareExpression(parser::CompareExprNode* node) {

}
void Visitor::visitLogicOp(parser::LogicExprNode::LogicOpOption* node) {

}
void Visitor::visitLogicExpression(parser::LogicExprNode* node) {

}