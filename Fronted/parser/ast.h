//
// Created by BALL on 2022/12/22.
//

#ifndef SAKORA_AST_H
#define SAKORA_AST_H

#include "../lexer/lex.h"

namespace parser {
    enum NodeKind {
        Token,

        // Expression
        CommaOp,                   // ','
        BasicExpression,
        BasicOp,                   // '.', '*'(unary), '&'(unary), '-'(unary)
        MulExpression,             // higher than BasicExpression
        MulOp,                     // '*', '/'
        AddExpression,             // higher than MulExpression
        AddOp,                     // '+', '-'
        CompareExpression,
        CompareOp,                 // '==', '!=', '<=', '<', '>=', '>'
        BooleanExpression,
        BooleanOp,                 // '&&', '||', '!'
        ListLiteralExpression,     // [r1, r2, r3, r4,r5]
        StructLiteralExpression,   // {i1: "hello", i2: 4}
        TupleLiteralExpression,    // (200, 300, 500)
        SymbolExpression,          // use: TypeofOp
        TypeofOp,
        AsExpression,              // ident as Type
        AsOp,
        WholeExpression,           /* use: AddExpression, BooleanExpression, ListLiteralExpression,
                                            StructLiteralExpression, TupleLiteralExpression, SymbolExpression */
        QualOp,                    // Qualifier: ':'

        // Stmt
        BlockStatement,
        LetStatement,              // use: DefinitionalExpression
        DefinitionalExpression,
    };

    struct Node {
        NodeKind kind;
        lexer::Token token = {lexer::NullToken, "Null", -1, -1};

        std::vector<Node> subs;

        explicit Node(NodeKind k);
        explicit Node(lexer::Token tok);
        Node(NodeKind k, lexer::Token tok);

        Node& operator[] (size_t index);
    };
}


#endif //SAKORA_AST_H
