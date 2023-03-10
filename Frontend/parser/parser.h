//
// Created by BALL on 2022/12/23.
//

#ifndef SAKORA_PARSER_H
#define SAKORA_PARSER_H

#include "ast_design.h"
#include "../../error/parser_error.h"

namespace parser {
    enum Marker {
        head = 0, ops = 1, factors = 2,
        mark = 0
    };

    class Parser {
        std::vector<lexer::Token> token_group;
        size_t pos = 0;
    public:
        Parser(std::vector<lexer::Token> tg);

        lexer::Token peek(size_t offset = 0);
        lexer::Token* seek();
        TokenNode* eat();
        // checker
        bool isBasicExprNode(); bool isBasicOpNode();
        #define isPrimExprNode isBasicExprNode
        bool isCallOpNode();
        bool isMulExprNode(); bool isMulOpNode();
        bool isAddExprNode(); bool isAddOpNode();
        bool isCompareExprNode(); bool isCompareOpNode();
        bool isLogicExprNode(); bool isLogicOpNode();
        bool isWholeExprNode();
        bool isBasicTypeExprNode();
        bool isFnTypeExprNode(); bool isTypeExprNode();
        bool isListLiteralExprNode();
        bool isStructLiteralExprNode();
        bool isAssignExprNode();
        bool isTypeofExprNode();
        bool isFnLikeExprNode();
        // parser
        IndexOpNode* parseIndexOpNode();
        CallOpNode* parseCallOpNode();
        MulExprNode::MulOpOption* parseMulExprOp();
        AddExprNode::AddOpOption* parseAddExprOp();
        CompareExprNode::CompareOpOption* parseCompareExprOp();
        LogicExprNode::LogicOpOption* parseLogicExprOp();

        PrimaryExprNode* parsePrimExprNode();
        BasicExprNode* parseBasicExprNode();
        MulExprNode* parseMulExprNode();
        AddExprNode* parseAddExprNode();
        CompareExprNode* parseCompareExprNode();
        LogicExprNode* parseLogicExprNode();
        ListLiteralExprNode* parseListLiteralExprNode();
        StructLiteralExprNode* parseStructLiteralExprNode();
        AssignExprNode* parseAssignExprNode();
        TypeofExprNode* parseTypeofExprNode();
        FunctionLikeExprNode* parseFunctionLikeExprNode();
        WholeExprNode* parseWholeExprNode();

        StructFlagOpNode* parseStructFlagOpNode();
        BasicTypeExprNode* parseBasicTypeExprNode();
        FnTypeExprNode* parseFnTypeExprNode();
        TypeExprNode* parseTypeExprNode();
    };
}


#endif //SAKORA_PARSER_H
