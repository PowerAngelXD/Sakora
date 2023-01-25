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
    struct TypeExprNode;
    struct WholeExprNode;
    struct AddExprNode;
    //

    // ExprDesign
    struct TokenNode {
        lexer::Token* token = nullptr;
    };
    
    struct AddOpNode { TokenNode* op = nullptr; };       struct EqOpNode { TokenNode* op = nullptr; };
    struct SubOpNode { TokenNode* op = nullptr; };       struct NeqOpNode { TokenNode* op = nullptr; };
    struct MulOpNode { TokenNode* op = nullptr; };       struct GtOpNode { TokenNode* op = nullptr; };
    struct DivOpNode { TokenNode* op = nullptr; };       struct LtOpNode { TokenNode* op = nullptr; };
    struct GeOpNode { TokenNode* op = nullptr; };        struct LeOpNode { TokenNode* op = nullptr; };
    struct LogicOrOpNode { TokenNode* op = nullptr; };   struct LogicAndOpNode { TokenNode* op = nullptr; };
    struct LogicNotOpNode { TokenNode* op = nullptr; };  struct GmemOpNode { TokenNode* op = nullptr; };
    struct CommaOpNode { TokenNode* op = nullptr; };     struct AssignOpNode {TokenNode* op = nullptr; };
    struct RestOpNode { TokenNode* op = nullptr; };      struct ListFlagOpNode { TokenNode* op = nullptr; };
    struct StructFlagOpNode {
        TokenNode* op = nullptr;
        ListFlagOpNode* list_flag = nullptr;
    };
    struct RefFlagOpNode { TokenNode* op = nullptr; };
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

        TypeExprNode* type = nullptr;
    };

    // Can be used as a separate statement
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

    // Can be used as a separate statement
    struct AssignExprNode {
        PrimaryExprNode* lval = nullptr;
        AssignOpNode* op = nullptr;
        WholeExprNode* rval = nullptr;
    };

    struct ListLiteralExprNode {
        TokenNode* bgn_sym = nullptr;
        std::vector<WholeExprNode*> elements;
        std::vector<TokenNode*> seps;
        TokenNode* end_sym = nullptr;
    };

    /**
     * Type literal expression
     * Example:
     * int32[] -> List of type int32
     * (int32, string, boolean) -> A tuple with element types of int32, string and boolean
     * struct MyStruct -> A structure named MyStruct
     * fn(int32, int32)->int32  ->  A function with a return value of int32 and two parameters of int32
     */
    struct BasicTypeExprNode {
        StructFlagOpNode* struct_flag = nullptr;
        TokenNode* basic_type = nullptr;
        ListFlagOpNode* list_flag = nullptr;
        RefFlagOpNode* ref_flag = nullptr;
    };

    struct TupleTypeExprNode {
        TokenNode* bgn_sym = nullptr;
        std::vector<TypeExprNode*> elements;
        std::vector<TokenNode*> seps;
        TokenNode* end_sym = nullptr;

        ListFlagOpNode* list_flag = nullptr; // is tuple list
    };

    struct FnTypeExprNode {
        TokenNode* mark = nullptr;
        TokenNode* bgn_sym = nullptr;
        std::vector<TypeExprNode*> elements;
        std::vector<TokenNode*> seps;
        TokenNode* end_sym = nullptr;

        TokenNode* ret_pointer = nullptr;
        TypeExprNode* ret_type = nullptr;
    };

    struct TypeExprNode {
        BasicTypeExprNode* basic_type = nullptr;
        TupleTypeExprNode* tuple_type = nullptr;
        FnTypeExprNode* fn_type = nullptr;
    };


    struct WholeExprNode {
        AddExprNode* add_expr = nullptr;
        LogicExprNode* logic_expr = nullptr;
        TypeExprNode* type_expr = nullptr;
    };

    // StmtDesign

    struct LetStmtNode {
        struct InitFactor {
            TokenNode* ident = nullptr;
            RestOpNode* type_restrict = nullptr;
            TypeExprNode* type = nullptr;
            AssignOpNode* assign_op = nullptr;
            WholeExprNode* value = nullptr;
        };
        TokenNode* mark = nullptr;
        std::vector<InitFactor*> inits;
        std::vector<TokenNode*> seps;
        TokenNode* end_mark = nullptr;
    };

    // Those special expressions that can be used as separate statements will become a branch of this statement
    struct ExprStmtNode {
        AssignExprNode* assign_expr = nullptr;
        PrimaryExprNode* prim_expr = nullptr;

        TokenNode* end_mark = nullptr;
    };

    struct IfStmtNode {
        TokenNode* mark = nullptr;
    };
}

#endif //SAKORA_AST_DESIGN_H
