//
// Created by BALL on 2022/12/25.
//

#include "visitor.h"

using namespace visitor;
using namespace parser;

std::string visitor::kind_to_string(CodeKind k) {
    switch (k) {
        case push_int: return "push_int";
        case push_deci: return "push_deci";
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
        case type_int:
            break;
        case type_deci:
            break;
        case type_str:
            break;
        case type_typeid:
            break;
        case set_list:
            break;
        case set_struct_array:
            break;
        case set_ref:
            break;
        case set_tuple:
            break;
        case set_struct:
            break;
        case push_bool:
            break;
        case type_bool:
            break;
        case push_flag:
            break;
    }
    return "null code";
}

Code::Code(CodeKind k, int l, int c): kind(k),val(0), ln(l), col(c) {}
Code::Code(CodeKind k, double v, int l, int c): kind(k), val(v), ln(l), col(c) {}

void Visitor::visitValToken(parser::TokenNode* node) {
    switch (node->token->kind) {
        case lexer::Number:
            if (node->token->content.find('.') != std::string::npos) {
                out.emplace_back(CodeKind::push_deci, std::stod(node->token->content), node->token->line, node->token->column);
            }
            else {
                out.emplace_back(CodeKind::push_int, static_cast<double>(std::stoi(node->token->content)), node->token->line, node->token->column);
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
    for (size_t i = 0; i < node->ops.size(); i ++) {
        visitBasicOp(node->ops[i]);
    }
}
void Visitor::visitPrimOp(parser::TokenNode* node) {
    out.emplace_back(CodeKind::gmem, node->token->line, node->token->column);
}
void Visitor::visitPrimExpression(parser::PrimaryExprNode* node) {
    if (node->head->head != nullptr) {
        visitBasicExpression(node->head->head);
    }
    else {
        visitWholeExpression(node->head->expr);
    }
    for (size_t i = 0; i < node->ops.size(); i ++) {
        if (node->head->head != nullptr) {
            visitBasicExpression(node->factors[i]->head);
        }
        else {
            visitWholeExpression(node->factors[i]->expr);
        }
        visitPrimOp(node->ops[i]->op);
    }
}
void Visitor::visitMulOp(parser::MulExprNode::MulOpOption* node) {
    if (node->mul_op != nullptr) out.emplace_back(CodeKind::mul, node->mul_op->op->token->line, node->mul_op->op->token->column);
    else if (node->div_op != nullptr) out.emplace_back(CodeKind::div, node->div_op->op->token->line, node->div_op->op->token->column);
}
void Visitor::visitMulExpression(parser::MulExprNode* node) {
    visitPrimExpression(node->head);
    for (size_t i = 0; i < node->ops.size(); i ++) {
        visitPrimExpression(node->factors[i]);
        visitMulOp(node->ops[i]);
    }
}   
void Visitor::visitAddOp(parser::AddExprNode::AddOpOption* node) {
    if (node->add_op != nullptr) out.emplace_back(CodeKind::add, node->add_op->op->token->line, node->add_op->op->token->column);
    else if (node->sub_op != nullptr) out.emplace_back(CodeKind::sub, node->sub_op->op->token->line, node->sub_op->op->token->column);
}
void Visitor::visitAddExpression(parser::AddExprNode* node) {
    visitMulExpression(node->head);
    for (size_t i = 0; i < node->ops.size(); i ++) {
        visitMulExpression(node->factors[i]);
        visitAddOp(node->ops[i]);
    }
}
void Visitor::visitCompareOp(parser::CompareExprNode::CompareOpOption* node) {
    if (node->eq_op != nullptr) out.emplace_back(CodeKind::eq, node->eq_op->op->token->line, node->eq_op->op->token->column);
    else if (node->neq_op != nullptr) out.emplace_back(CodeKind::neq, node->neq_op->op->token->line, node->neq_op->op->token->column);
    else if (node->gt_op != nullptr) out.emplace_back(CodeKind::gt, node->gt_op->op->token->line, node->gt_op->op->token->column);
    else if (node->ge_op != nullptr) out.emplace_back(CodeKind::ge, node->ge_op->op->token->line, node->ge_op->op->token->column);
    else if (node->lt_op != nullptr) out.emplace_back(CodeKind::lt, node->lt_op->op->token->line, node->lt_op->op->token->column);
    else if (node->le_op != nullptr) out.emplace_back(CodeKind::le, node->le_op->op->token->line, node->le_op->op->token->column);

}
void Visitor::visitCompareExpression(parser::CompareExprNode* node) {
    visitAddExpression(node->head);
    for (size_t i = 0; i < node->ops.size(); i ++) {
        visitAddExpression(node->factors[i]);
        visitCompareOp(node->ops[i]);
    }
}
void Visitor::visitLogicOp(parser::LogicExprNode::LogicOpOption* node) {
    if (node->logic_and_op != nullptr) out.emplace_back(CodeKind::logic_and, node->logic_and_op->op->token->line, node->logic_and_op->op->token->column);
    else if (node->logic_or_op != nullptr) out.emplace_back(CodeKind::logic_or, node->logic_or_op->op->token->line, node->logic_or_op->op->token->column);
    else if (node->logic_not_op != nullptr) out.emplace_back(CodeKind::logic_not, node->logic_not_op->op->token->line, node->logic_not_op->op->token->column);
}
void Visitor::visitLogicExpression(parser::LogicExprNode* node) {
    if (node->ops[0]->logic_not_op != nullptr) {
        visitCompareExpression(node->head);
        out.emplace_back(CodeKind::logic_not, node->ops[0]->logic_not_op->op->token->line, node->ops[0]->logic_not_op->op->token->column);
    }
    else {
        visitCompareExpression(node->head);
        for (size_t i = 0; i < node->ops.size(); i ++) {
            visitCompareExpression(node->factors[i]);
            visitLogicOp(node->ops[i]);
        }
    }
}

void Visitor::visitWholeExpression(parser::WholeExprNode *node) {
    if (node->add_expr != nullptr) visitAddExpression(node->add_expr);
    else if (node->logic_expr != nullptr) visitLogicExpression(node->logic_expr);
}

void Visitor::visitBasicTypeExpression(parser::BasicTypeExprNode* node) {
    auto type_content = node->basic_type->token->content;
    if (type_content == "int")
        out.emplace_back(CodeKind::type_int, node->basic_type->token->line, node->basic_type->token->column);
    if (type_content == "deci")
        out.emplace_back(CodeKind::type_deci, node->basic_type->token->line, node->basic_type->token->column);
    else if (type_content == "bool")
        out.emplace_back(CodeKind::type_bool, node->basic_type->token->line, node->basic_type->token->column);
    else if (type_content == "typeid")
        out.emplace_back(CodeKind::type_typeid, node->basic_type->token->line, node->basic_type->token->column);
    else if (type_content == "str")
        out.emplace_back(CodeKind::type_str, node->basic_type->token->line, node->basic_type->token->column);
    else {
        constantPool.push_back(type_content);
        out.emplace_back(CodeKind::push_str, constantPool.size() - 1, node->basic_type->token->line, node->basic_type->token->column);
    }

    if (node->struct_flag != nullptr) {
        if (node->struct_flag->list_flag != nullptr)
            out.emplace_back(CodeKind::set_struct_array, node->basic_type->token->line, node->basic_type->token->column);
        else
            out.emplace_back(CodeKind::set_struct, node->basic_type->token->line, node->basic_type->token->column);
    }
    else if (node->list_flag != nullptr)
        out.emplace_back(CodeKind::set_list, node->basic_type->token->line, node->basic_type->token->column);
    else if (node->ref_flag != nullptr)
        out.emplace_back(CodeKind::set_ref, node->basic_type->token->line, node->basic_type->token->column);
}
//void Visitor::visitTupleTypeExpression(parser::TupleTypeExprNode* node) {
//
//}
//void Visitor::visitFnTypeExpression(parser::FnTypeExprNode* node) {
//
//}
//void Visitor::visitTypeExpression(parser::TypeExprNode* node) {
//
//}
