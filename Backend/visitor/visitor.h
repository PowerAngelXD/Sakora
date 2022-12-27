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
        add, sub, mul, div, gmem, mod
    };
    std::string kind_to_string(CodeKind k);

    struct Code {
        CodeKind kind;
        double val;
        int ln, col;

        Code(CodeKind k, int l, int c);
        Code(CodeKind k, double v, int l, int c);
    };

    class Visitor {
        // visiting source
        parser::Node source;
    public:
        std::vector<Code> out;
        std::vector<std::string> constantPool;

        Visitor(parser::Node src);

        // Expression Visitor
        void visitValToken(const parser::Node& node);
        void visitBasicOp(const parser::Node& node); void visitBasicExpression(parser::Node node);
        void visitMulOp(const parser::Node& node); void visitMulExpression(parser::Node node);
        void visitAddOp(const parser::Node& node); void visitAddExpression(parser::Node node);
        //
    };
}

#endif //SAKORA_VISITOR_H
