//
// Created by BALL on 2022/12/25.
//

#ifndef SAKORA_VISITOR_H
#define SAKORA_VISITOR_H

#include "../../Fronted/parser/parser.h"

namespace visitor {
    enum CodeKind {
        push_float, push_double, push_i16, push_i32, push_i64, push_bool, push_str,
        // calc
        add, sub, mul, div
    };

    struct Code {
        CodeKind kind;
        double val;
        int ln, col;

        Code(CodeKind k, int l, int c);
        Code(CodeKind k, double v, int l, int c);
    };

    class Visitor {
        parser::Node source;
        std::vector<Code> out;
        std::vector<std::string> constantPool;
    };
}

#endif //SAKORA_VISITOR_H
