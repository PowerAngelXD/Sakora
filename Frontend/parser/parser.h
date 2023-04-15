//
// Created by BALL on 2022/12/23.
//

#ifndef SAKORA_PARSER_H
#define SAKORA_PARSER_H

#include "ast_design.h"
#include "../../error/parser_error.h"

#define SAK_PARSER_ERROR_CATCH catch (parser_error::UnexpectedTokenError& e) {e.printError();} \
                    catch (parser_error::SyntaxError& e) {e.printError();} \
                    catch (lexer_error::IllegalSymbolError& e) {e.printError();} \
                    catch (lexer_error::StringUnCloseError& e) {e.printError();} \
                    catch (lexer_error::NotCorrectNumberError& e) {e.printError();}

#define SAK_STORAGE_ERROR_CATCH catch (storage_error::UnsupportedOperationError& e) {e.printError();} \
                    catch (storage_error::UnknownIdentifierError& e) {e.printError();} \
                    catch (storage_error::DuplicateIdentifierError& e) {e.printError();} \
                    catch (storage_error::IllegalTypeDescriptionError& e) {e.printError();}

namespace parser {
    class Parser {
        std::vector<lexer::Token> token_group;
        size_t pos = 0;
    public:
        Parser(std::vector<lexer::Token> tg);

        lexer::Token peek(size_t offset = 0);
        lexer::Token* seek();
        TokenNode* eat();

        // Expression
        // checker
        bool isBasicExprNode(); bool isBasicOpNode();
        #define isPrimExprNode isBasicExprNode
        bool isCallOpNode();
        bool isMulExprNode(); bool isMulOpNode();
        bool isAddExprNode(); bool isAddOpNode();
        bool isCompareExprNode(); bool isCompareOpNode();
        bool isLogicExprNode(); bool isLogicOpNode();
        bool isWholeExprNode();
        bool isUnitTypeExprNode(); bool isBasicTypeExprNode();
        bool isListFlagOpNode(); bool isFnTypeExprNode(); bool isTypeExprNode();
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

        ListFlagOpNode* parseListFlagOpNode();
        StructFlagOpNode* parseStructFlagOpNode();
        UnitTypeExprNode* parseUnitTypeExprNode();
        BasicTypeExprNode* parseBasicTypeExprNode();
        FnTypeExprNode* parseFnTypeExprNode();
        TypeExprNode* parseTypeExprNode();


        // Stmts
        // checker
        bool isLetStmtNode(); bool isExprStmtNode(); bool isIfStmtNode();
        bool isBlockStmtNode();

        LetStmtNode* parseLetStmtNode();
        ExprStmtNode* parseExprStmtNode();
        IfStmtNode* parseIfStmtNode();
        BlockStmtNode* parseBlockStmtNode();


        // Whole Parser
        bool isProgramSection();
        bool isProgram();

        ProgramSectionNode* generateSection();
        ProgramObject* generateProgramObject();
    };
}


#endif //SAKORA_PARSER_H
