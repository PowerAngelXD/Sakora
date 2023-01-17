//
// Created by BALL on 2022/12/25.
//

#ifndef SAKORA_VISITOR_H
#define SAKORA_VISITOR_H

#include "../../Fronted/parser/parser.h"

namespace visitor {
    enum CodeKind {
        push_float, push_double, push_i16, push_i32, push_i64, push_bool, push_str, push_iden,
        // calc
        add, sub, mul, div, gmem, mod,
        eq, neq, gt, lt, ge, le, logic_not, logic_and, logic_or
    };
    std::string kind_to_string(CodeKind k);

    struct Code {
        CodeKind kind;
        double val;
        int ln, col;

        Code(CodeKind k, int l, int c);
        Code(CodeKind k, double v, int l, int c);
    };

    struct Visitor {
        std::vector<Code> out;
        std::vector<std::string> constantPool;

        // Expression Visitor
        void visitValToken(parser::TokenNode* node);
        void visitBasicOp(parser::BasicExprNode::CallingOpOption* node); void visitBasicExpression(parser::BasicExprNode* node);
        void visitPrimOp(parser::TokenNode* node); void visitPrimExpression(parser::PrimaryExprNode* node);
        void visitMulOp(parser::MulExprNode::MulOpOption* node); void visitMulExpression(parser::MulExprNode* node);
        void visitAddOp(parser::AddExprNode::AddOpOption* node); void visitAddExpression(parser::AddExprNode* node);
        void visitCompareOp(parser::CompareExprNode::CompareOpOption* node); void visitCompareExpression(parser::CompareExprNode* node);
        void visitLogicOp(parser::LogicExprNode::LogicOpOption* node); void visitLogicExpression(parser::LogicExprNode* node);
        void visitWholeExpression(parser::WholeExprNode* node);
        //
    };
}

#endif //SAKORA_VISITOR_H
