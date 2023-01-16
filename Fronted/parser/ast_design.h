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
        std::vector<WholeExprNode*> factors;
        std::vector<CommaOpNode*> seps;
        TokenNode* right = nullptr;
    };
    struct BasicExprNode {
        struct CallingOpOption {
            IndexOpNode* index_op = nullptr;
            CallOpNode* call_op = nullptr;
        };

        TokenNode* factor = nullptr;
        std::vector<CallingOpOption*> ops;
    };

    struct PrimaryExprNode {
        struct Factor {
            BasicExprNode* head = nullptr;

            TokenNode* left = nullptr;
            WholeExprNode* expr = nullptr;
            TokenNode* right = nullptr;
        };
        Factor* head = nullptr;
        std::vector<Factor*> factors;
        std::vector<GmemOpNode*> ops;
    };

    struct MulExprNode {
        struct MulOpOption {
            MulOpNode* mul_op = nullptr;
            DivOpNode* div_op = nullptr;
        };

        PrimaryExprNode* head = nullptr;
        std::vector<MulOpOption*> ops;
        std::vector<PrimaryExprNode*> factors;
    };

    struct AddExprNode {
        struct AddOpOption {
            AddOpNode* add_op = nullptr;
            SubOpNode* sub_op = nullptr;
        };

        MulExprNode* head = nullptr;
        std::vector<AddOpOption *> ops;
        std::vector<MulExprNode*> factors;
    };

    struct CompareExprNode {
        struct CompareOpOption {
            EqOpNode* eq_op = nullptr;
            NeqOpNode* neq_op = nullptr;
            GtOpNode* gt_op = nullptr;
            LtOpNode* lt_op = nullptr;
            GeOpNode* ge_op = nullptr;
            LeOpNode* le_op = nullptr;
        };

        AddExprNode* head = nullptr;
        std::vector<CompareOpOption*> ops;
        std::vector<AddExprNode*> factors;
    };

    struct LogicExprNode {
        struct LogicOpOption {
            LogicAndOpNode* logic_and_op = nullptr;
            LogicNotOpNode* logic_not_op = nullptr;
            LogicOrOpNode* logic_or_op = nullptr;
        };

        CompareExprNode* head = nullptr;
        std::vector<LogicOpOption*> ops;
        std::vector<CompareExprNode*> factors;
    };

    struct WholeExprNode {
        AddExprNode* add_expr = nullptr;
        LogicExprNode* logic_expr = nullptr;
    };
}

#endif //SAKORA_AST_DESIGN_H
