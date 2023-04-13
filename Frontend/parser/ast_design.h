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
    struct ProgramSectionNode;
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
    struct RestOpNode { TokenNode* op = nullptr; };
    struct ListFlagOpNode {
        TokenNode* left = nullptr;
        TokenNode* ref = nullptr;
        TokenNode* right = nullptr;
    };
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

    // Special operators
    struct TypeofExprNode {
        TokenNode* mark = nullptr;
        CallOpNode* calling = nullptr;
    };

    struct FunctionLikeExprNode {
        TypeofExprNode* typeof_expr = nullptr;
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

    struct ListLiteralExprNode {
        // Array: [1, 2, 3, 4]
        // Vararrar: mutable [1, 2, 3, 4]
        TokenNode* mut_mark = nullptr;
        TokenNode* bgn = nullptr;
        std::vector<WholeExprNode*> elements;
        std::vector<TokenNode*> seps;
        TokenNode* end = nullptr;
    };

    struct StructLiteralExprNode {
        struct KeyPair {
            TokenNode* key = nullptr;
            RestOpNode* rest = nullptr;
            WholeExprNode* value = nullptr;
        };

        TokenNode* bgn = nullptr;
        std::vector<KeyPair*> pairs;
        std::vector<TokenNode*> seps;
        TokenNode* end = nullptr;
    };

    // Can be used as a separate statement
    struct AssignExprNode {
        PrimaryExprNode* lval = nullptr;
        AssignOpNode* op = nullptr;
        WholeExprNode* rval = nullptr;
    };

    /**
     * Type literal expression
     * Example:
     * int[] -> List of type int
     * (int, string, boolean) -> A tuple with element types of int, string and boolean
     * struct MyStruct -> A structure named MyStruct
     * fn(int, int)->int  ->  A function with a return value of int and two parameters of int
     */
    struct UnitTypeExprNode {
        TokenNode* basic_type = nullptr;

        StructFlagOpNode* struct_op = nullptr;
    };

    struct BasicTypeExprNode {
        UnitTypeExprNode* unit = nullptr;

        ListFlagOpNode* list_flag = nullptr;
        RefFlagOpNode* ref_flag = nullptr;
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
        FnTypeExprNode* fn_type = nullptr;
    };


    struct WholeExprNode {
        AddExprNode* add_expr = nullptr;
        LogicExprNode* logic_expr = nullptr;
        TypeExprNode* type_expr = nullptr;
        ListLiteralExprNode* list_expr = nullptr;
        StructFlagOpNode* struct_expr = nullptr;
        FunctionLikeExprNode* fnlike_expr = nullptr;
    };

    // StmtDesign

    struct LetStmtNode {
        struct InitFactor {
            TokenNode* ident = nullptr;
            RestOpNode* type_restrict = nullptr; // ':'
            TypeExprNode* type = nullptr;
            AssignOpNode* assign_op = nullptr;   // '='
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

    // ProgramObject, or SubProgram
    typedef std::vector<ProgramSectionNode> ProgramObject;

    struct BlockStmtNode {
        TokenNode* bgn = nullptr;
        ProgramObject* sub_program = nullptr;
        TokenNode* end = nullptr;
    };

    struct IfStmtNode {
        TokenNode* mark = nullptr;

        TokenNode* bgn = nullptr;
        LogicExprNode* condition = nullptr;
        TokenNode* end = nullptr;

        BlockStmtNode* body = nullptr;
    };

    // ProgramSystem Design

    struct ProgramSectionNode {
        LetStmtNode* letstmt = nullptr;
        ExprStmtNode* exprstmt = nullptr;
        IfStmtNode* ifstmt = nullptr;
    };
}

#endif //SAKORA_AST_DESIGN_H
