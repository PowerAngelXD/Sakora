//
// Created by BALL on 2023/1/13.
//

#ifndef SAKORA_AST_DESIGN_H
#define SAKORA_AST_DESIGN_H

#include "../lexer/lex.h"
#include <tuple>

#define TG(idx, tp) std::get<idx>(tp)

namespace parser {
    // pre defined
    struct WholeExprNode;
    struct AddExprNode;
    //

    struct TokenNode {
        lexer::Token* token = nullptr;
    };
    
    struct AddOpNode { TokenNode* op = nullptr; };      struct EqOpNode { TokenNode* op = nullptr; };
    struct SubOpNode { TokenNode* op = nullptr; };      struct NeqOpNode { TokenNode* op = nullptr; };
    struct MulOpNode { TokenNode* op = nullptr; };      struct GtOpNode { TokenNode* op = nullptr; };
    struct DivOpNode { TokenNode* op = nullptr; };      struct LtOpNode { TokenNode* op = nullptr; };
    struct GeOpNode { TokenNode* op = nullptr; };       struct LeOpNode { TokenNode* op = nullptr; };
    struct LogicOrOpNode { TokenNode* op = nullptr; };  struct LogicAndOpNode { TokenNode* op = nullptr; };
    struct LogicNotOpNode { TokenNode* op = nullptr; }; struct GmemOpNode { TokenNode* op = nullptr; };
    struct CommaOpNode { TokenNode* op = nullptr; };
    struct IndexOpNode {
        TokenNode* left = nullptr;
        AddExprNode* index = nullptr;
        TokenNode* right = nullptr;
    };
    struct CallOpNode {
        TokenNode* left = nullptr;
        std::vector<WholeExprNode*>* factors = nullptr;
        std::vector<CommaOpNode*>* seps = nullptr;
        TokenNode* right = nullptr;
    };
    struct BasicExprNode {
        typedef std::tuple<IndexOpNode*, CallOpNode*> CallingOption;
        static const size_t IndexOp = 0, CallOp = 1;

        TokenNode* factor = nullptr;
        std::vector<CallingOption*>* ops = nullptr;
    };

    struct PrimaryExprNode {
        struct Factor {
            BasicExprNode* head = nullptr;

            TokenNode* left = nullptr;
            WholeExprNode* expr = nullptr;
            TokenNode* right = nullptr;
        };
        Factor* head = nullptr;
        std::vector<Factor*>* factors = nullptr;
        std::vector<GmemOpNode*>* ops = nullptr;
    };

    struct MulExprNode {
        typedef std::tuple<MulOpNode*, DivOpNode*> MulOption;
        static const size_t MulOp = 0, DivOp = 1;

        PrimaryExprNode* head = nullptr;
        std::vector<MulOption*>* ops = nullptr;
        std::vector<PrimaryExprNode*>* factors = nullptr;
    };

    struct AddExprNode {
        typedef std::tuple<AddOpNode*, SubOpNode*> AddOption;
        static const size_t AddOp = 0, SubOp = 1;

        MulExprNode* head = nullptr;
        std::vector<AddOption *>* ops = nullptr;
        std::vector<MulExprNode*>* factors = nullptr;
    };

    struct CompareExprNode {
        typedef std::tuple<EqOpNode*, NeqOpNode*, GtOpNode*, LtOpNode*, GeOpNode*, LeOpNode*> CompareOption;
        static const size_t EqOp = 0, NeqOp = 1, GtOp = 2, LtOp = 3, GeOp = 4, LeOp = 5;

        AddExprNode* head = nullptr;
        std::vector<CompareOption*>* ops = nullptr;
        std::vector<AddExprNode*>* factors = nullptr;
    };

    struct LogicExprNode {
        typedef std::tuple<LogicAndOpNode*, LogicOrOpNode*, LogicNotOpNode*> LogicOption;
        static const size_t LogicAndOp = 0, LogicOrOp = 1, LogicNotOp = 2;

        CompareExprNode* head = nullptr;
        std::vector<LogicOption*>* ops = nullptr;
        std::vector<CompareExprNode*>* factors = nullptr;
    };

    struct WholeExprNode {
        AddExprNode* add_expr = nullptr;
        LogicExprNode* logic_expr = nullptr;
    };
}

#endif //SAKORA_AST_DESIGN_H
