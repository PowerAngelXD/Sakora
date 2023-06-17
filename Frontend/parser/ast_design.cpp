//
// Created by BALL on 2023/1/13.
//

#include "ast_design.h"

std::string parser::TokenNode::to_string() {
    return "{<Token>, " + this->token->content + "}";
}

// Operators

std::string parser::AddOpNode::to_string() {
    return "{Add(+)}";
}

std::string parser::EqOpNode::to_string() {
    return "{Eq(==)}";
}

std::string parser::SubOpNode::to_string() {
    return "{Sub(-)}";
}

std::string parser::NeqOpNode::to_string() {
    return "{Neq(!=)}";
}

std::string parser::MulOpNode::to_string() {
    return "{Mul(*)}";
}

std::string parser::GtOpNode::to_string() {
    return "{Gt(>)}";
}

std::string parser::DivOpNode::to_string() {
    return "{Div(/)}";
}

std::string parser::LtOpNode::to_string() {
    return "{Lt(<)}";
}

std::string parser::GeOpNode::to_string() {
    return "{Ge(>=)}";
}

std::string parser::LeOpNode::to_string() {
    return "{Le(<=)}";
}

std::string parser::LogicOrOpNode::to_string() {
    return "{LogicOr(||)}";
}

std::string parser::LogicAndOpNode::to_string() {
    return "{LogicAnd(&&)}";
}

std::string parser::LogicNotOpNode::to_string() {
    return "{LogicNot(!)}";
}

std::string parser::GmemOpNode::to_string() {
    return "{GmemOp(.)}";
}

std::string parser::CommaOpNode::to_string() {
    return "{CommaOp(,)}";
}

std::string parser::AssignOpNode::to_string() {
    return "{AssignOp(=)}";
}

std::string parser::RestOpNode::to_string() {
    return "{RestOp(:)}";
}

std::string parser::ListFlagOpNode::to_string() {
    return "{ListFlagOp( [] )}";
}

std::string parser::StructFlagOpNode::to_string() {
    return "{StructFlagOp( struct )}";
}

std::string parser::RefFlagOpNode::to_string() {
    return "{RefFlagOp(&)}";
}

std::string parser::IndexOpNode::to_string() {
    return "{IndexOp, <index>:" + this->index->to_string() + "}";
}

std::string parser::CallOpNode::to_string() {
    std::string ret = "{CallOp, args: [";
    for (size_t i = 0; i < this->factors.size(); i ++) {
        if (i == this->factors.size() - 1)
            break;

        ret += this->factors[i]->to_string();
        ret += ", ";
    }
    ret += "}";

    return ret;
}


// Expr
std::string parser::BasicExprNode::to_string() {
    std::string ret = "{BasicExprNode, ";
    if (this->type != nullptr)
        ret += this->type->to_string();
    else {
        ret += this->factor->to_string();
        for (size_t i = 0; i < this->ops.size(); i ++) {
            if (i == this->ops.size() - 1)
                break;

            if (this->ops[i]->call_op != nullptr)
                ret += this->ops[i]->call_op->to_string();
            else ret += this->ops[i]->index_op->to_string();
            ret += ", ";
        }
    }
    return ret;
}

std::string parser::TypeofExprNode::to_string() {
    return "{TypeOfExprNode, " + this->calling->to_string() + "}";
}

std::string parser::FunctionLikeExprNode::to_string() {
    if (typeof_expr != nullptr ) return typeof_expr->to_string();
    else  return "null";
}

std::string parser::PrimaryExprNode::Factor::to_string() {
    return std::string();
}

std::string parser::PrimaryExprNode::to_string() {
    std::string ret = "{PrimaryExprNode";
    return std::string();
}

std::string parser::MulExprNode::to_string() {
    return std::string();
}

std::string parser::AddExprNode::to_string() {
    return std::string();
}

std::string parser::CompareExprNode::to_string() {
    return std::string();
}

std::string parser::LogicExprNode::to_string() {
    return std::string();
}

std::string parser::ListLiteralExprNode::to_string() {
    return std::string();
}

std::string parser::StructLiteralExprNode::to_string() {
    return std::string();
}

std::string parser::AssignExprNode::to_string() {
    return std::string();
}

std::string parser::UnitTypeExprNode::to_string() {
    return std::string();
}

std::string parser::BasicTypeExprNode::to_string() {
    return std::string();
}

std::string parser::FnTypeExprNode::to_string() {
    return std::string();
}

std::string parser::TypeExprNode::to_string() {
    return std::string();
}

std::string parser::WholeExprNode::to_string() {
    return std::string();
}

std::string parser::LetStmtNode::to_string() {
    return std::string();
}

std::string parser::ExprStmtNode::to_string() {
    return std::string();
}

std::string parser::BlockStmtNode::to_string() {
    return std::string();
}

std::string parser::IfStmtNode::to_string() {
    return std::string();
}

std::string parser::ProgramSectionNode::to_string() {
    return std::string();
}
