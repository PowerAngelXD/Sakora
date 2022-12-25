//
// Created by BALL on 2022/12/23.
//

#ifndef SAKORA_PARSER_H
#define SAKORA_PARSER_H
#include "ast.h"

namespace parser {
    class Parser {
        std::vector<lexer::Token> token_group;
        size_t pos = 0;
    public:
        Parser(std::vector<lexer::Token> tg);

        lexer::Token peek(size_t offset = 0);
        lexer::Token eat();
        // checker
        bool isBasicExpressionNode(); bool isBasicOpNode();
        bool isMulExpressionNode(); bool isMulOpNode();
        bool isAddExpressionNode(); bool isAddOpNode();
        bool isCompareExpressionNode(); bool isCompareOpNode();
        bool isBooleanExpressionNode(); bool isBooleanOpNode();
        bool isWholeExpressionNode();
        // parser
        Node parseBasicExpressionNode(); Node parseBasicOpNode();
        Node parseMulExpressionNode(); Node parseMulOpNode();
        Node parseAddExpressionNode(); Node parseAddOpNode();
        Node parseCompareExpressionNode(); Node parseCompareOpNode();
        Node parseBooleanExpressionNode(); Node parseBooleanOpNode();
    };
}


#endif //SAKORA_PARSER_H
