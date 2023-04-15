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

        std::string to_string();
    };

    // Operators
    struct AddOpNode {
        TokenNode* op = nullptr;

        std::string to_string();
    };
    struct EqOpNode {
        TokenNode* op = nullptr;

        std::string to_string();
    };
    struct SubOpNode {
        TokenNode* op = nullptr;

        std::string to_string();
    };
    struct NeqOpNode {
        TokenNode* op = nullptr;

        std::string to_string();
    };
    struct MulOpNode {
        TokenNode* op = nullptr;

        std::string to_string();
    };
    struct GtOpNode {
        TokenNode* op = nullptr;

        std::string to_string();
    };
    struct DivOpNode {
        TokenNode* op = nullptr;

        std::string to_string();
    };
    struct LtOpNode {
        TokenNode* op = nullptr;

        std::string to_string();
    };
    struct GeOpNode {
        TokenNode* op = nullptr;

        std::string to_string();
    };
    struct LeOpNode {
        TokenNode* op = nullptr;

        std::string to_string();
    };
    struct LogicOrOpNode {
        TokenNode* op = nullptr;

        std::string to_string();
    };
    struct LogicAndOpNode {
        TokenNode* op = nullptr;

        std::string to_string();
    };
    struct LogicNotOpNode {
        TokenNode* op = nullptr;

        std::string to_string();
    };
    struct GmemOpNode {
        TokenNode* op = nullptr;

        std::string to_string();
    };
    struct CommaOpNode {
        TokenNode* op = nullptr;

        std::string to_string();
    };
    struct AssignOpNode {
        TokenNode* op = nullptr;

        std::string to_string();
    };
    struct RestOpNode {
        TokenNode* op = nullptr;

        std::string to_string();
    };
    struct ListFlagOpNode {
        TokenNode* left = nullptr;
        TokenNode* ref = nullptr;
        TokenNode* right = nullptr;

        std::string to_string();
    };
    struct StructFlagOpNode {
        TokenNode* op = nullptr;
        ListFlagOpNode* list_flag = nullptr;

        std::string to_string();
    };
    struct RefFlagOpNode {
        TokenNode* op = nullptr;

        std::string to_string();
    };
    struct IndexOpNode {
        TokenNode* left = nullptr;
        AddExprNode* index = nullptr;
        TokenNode* right = nullptr;

        std::string to_string();
    };
    struct CallOpNode {
        TokenNode* left = nullptr;
        std::vector<WholeExprNode*> factors;
        std::vector<CommaOpNode*> seps;
        TokenNode* right = nullptr;

        std::string to_string();
    };
    //

    struct BasicExprNode {
        struct CallingOpOption {
            IndexOpNode* index_op = nullptr;
            CallOpNode* call_op = nullptr;
        };

        TokenNode* factor = nullptr;
        std::vector<CallingOpOption*> ops;

        TypeExprNode* type = nullptr;

        std::string to_string();
    };

    // Special operators
    struct TypeofExprNode {
        TokenNode* mark = nullptr;
        CallOpNode* calling = nullptr;

        std::string to_string();
    };

    struct FunctionLikeExprNode {
        TypeofExprNode* typeof_expr = nullptr;

        std::string to_string();
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

        std::string to_string();
    };

    struct MulExprNode {
        struct MulOpOption {
            MulOpNode* mul_op = nullptr;
            DivOpNode* div_op = nullptr;
        };

        PrimaryExprNode* head = nullptr;
        std::vector<MulOpOption*> ops;
        std::vector<PrimaryExprNode*> factors;

        std::string to_string();
    };

    struct AddExprNode {
        struct AddOpOption {
            AddOpNode* add_op = nullptr;
            SubOpNode* sub_op = nullptr;
        };

        MulExprNode* head = nullptr;
        std::vector<AddOpOption *> ops;
        std::vector<MulExprNode*> factors;

        std::string to_string();
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

        std::string to_string();
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

        std::string to_string();
    };

    struct ListLiteralExprNode {
        // Array: [1, 2, 3, 4]
        // Vararrar: mutable [1, 2, 3, 4]
        TokenNode* mut_mark = nullptr;
        TokenNode* bgn = nullptr;
        std::vector<WholeExprNode*> elements;
        std::vector<TokenNode*> seps;
        TokenNode* end = nullptr;

        std::string to_string();
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

        std::string to_string();
    };

    // Can be used as a separate statement
    struct AssignExprNode {
        PrimaryExprNode* lval = nullptr;
        AssignOpNode* op = nullptr;
        WholeExprNode* rval = nullptr;

        std::string to_string();
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

        std::string to_string();
    };

    struct BasicTypeExprNode {
        UnitTypeExprNode* unit = nullptr;

        ListFlagOpNode* list_flag = nullptr;
        RefFlagOpNode* ref_flag = nullptr;

        std::string to_string();
    };

    struct FnTypeExprNode {
        TokenNode* mark = nullptr;
        TokenNode* bgn_sym = nullptr;
        std::vector<TypeExprNode*> elements;
        std::vector<TokenNode*> seps;
        TokenNode* end_sym = nullptr;

        TokenNode* ret_pointer = nullptr;
        TypeExprNode* ret_type = nullptr;

        std::string to_string();
    };

    struct TypeExprNode {
        BasicTypeExprNode* basic_type = nullptr;
        FnTypeExprNode* fn_type = nullptr;

        std::string to_string();
    };


    struct WholeExprNode {
        AddExprNode* add_expr = nullptr;
        LogicExprNode* logic_expr = nullptr;
        TypeExprNode* type_expr = nullptr;
        ListLiteralExprNode* list_expr = nullptr;
        StructFlagOpNode* struct_expr = nullptr;
        FunctionLikeExprNode* fnlike_expr = nullptr;

        std::string to_string();
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

        std::string to_string();
    };

    // Those special expressions that can be used as separate statements will become a branch of this statement
    struct ExprStmtNode {
        AssignExprNode* assign_expr = nullptr;
        PrimaryExprNode* prim_expr = nullptr;

        TokenNode* end_mark = nullptr;

        std::string to_string();
    };

    // ProgramObject, or SubProgram
    typedef std::vector<ProgramSectionNode*> ProgramObject;

    struct BlockStmtNode {
        TokenNode* bgn = nullptr;
        ProgramObject* sub_program = nullptr;
        TokenNode* end = nullptr;

        std::string to_string();
    };

    struct IfStmtNode {
        TokenNode* mark = nullptr;

        TokenNode* bgn = nullptr;
        LogicExprNode* condition = nullptr;
        TokenNode* end = nullptr;

        BlockStmtNode* body = nullptr;

        std::string to_string();
    };

    // ProgramSystem Design

    struct ProgramSectionNode {
        LetStmtNode* letstmt = nullptr;
        ExprStmtNode* exprstmt = nullptr;
        IfStmtNode* ifstmt = nullptr;
        BlockStmtNode* blockstmt = nullptr;

        std::string to_string();
    };
}

#endif //SAKORA_AST_DESIGN_H
