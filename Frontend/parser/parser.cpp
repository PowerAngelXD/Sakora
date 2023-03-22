//
// Created by BALL on 2022/12/23.
//

#include "parser.h"
#include "ast_design.h"

#include <utility>

using namespace parser;

parser::Parser::Parser(std::vector<lexer::Token> tg):
    token_group(std::move(tg)) {}

lexer::Token Parser::peek(size_t offset) {
    return token_group[pos + offset];
}
lexer::Token* Parser::seek() {
    return new lexer::Token(token_group[pos]);
}
TokenNode* Parser::eat() {
    return new TokenNode {new lexer::Token(token_group[pos ++])};
}

// checker

bool Parser::isBasicExprNode() {
    return peek().kind != lexer::NullToken && peek().content != "[" && peek().kind != lexer::Keyword;
}
bool Parser::isBasicOpNode() {
    return peek().content == ".";
}
bool Parser::isCallOpNode() {
    return peek().content == "(";
}
bool Parser::isMulExprNode() {
    return isBasicExprNode();
}
bool Parser::isMulOpNode() {
    return peek().content == "*" || peek().content == "/" || peek().content == "%";
}
bool Parser::isAddExprNode() {
    return isMulExprNode();
}
bool Parser::isAddOpNode() {
    return peek().content == "+" || peek().content == "-";
}
bool Parser::isCompareExprNode() {
    auto temp = pos;
    if (isAddExprNode()) {
        parseAddExprNode(); // ignore the returned value
        if (isCompareOpNode()) { pos = temp; return true; }
        else { pos = temp; return false; }
    }
    return false;
}
bool Parser::isCompareOpNode() {
    return peek().content == "==" || peek().content == "!=" ||
           peek().content == ">=" || peek().content == "<=" ||
           peek().content == ">" || peek().content == "<";
}
bool Parser::isLogicExprNode() {
    return isCompareExprNode() || peek().content == "!";
}
bool Parser::isLogicOpNode() {
    return peek().content == "||" || peek().content == "&&" || peek().content == "!";
}
bool Parser::isWholeExprNode() {
    return isAddExprNode() || isLogicExprNode() || isListLiteralExprNode() || isStructLiteralExprNode() || isFnLikeExprNode();
}
bool Parser::isListLiteralExprNode() {
    return peek().content == "[" || (peek().content == "mutable" && peek(1).content == "[");
}
bool Parser::isStructLiteralExprNode() {
    return peek().content == "{";
}
bool Parser::isAssignExprNode() {
    auto temp = pos;
    if (isPrimExprNode()) {
        parsePrimExprNode(); // ignore the returned value
        if (peek().content == "=") { pos = temp; return true; }
        else { pos = temp; return false; }
    }
    return false;
}
bool Parser::isBasicTypeExprNode() {
    if (peek().content == "struct"&& peek(1).kind == lexer::TokenKind::Ident) return true;
    else if (peek().kind == lexer::TokenKind::Ident) return true;
    else return false;
}
bool Parser::isFnTypeExprNode() {
    return peek().content == "fn";
}
bool Parser::isFnLikeExprNode() {
    return isTypeofExprNode();
}
bool Parser::isTypeofExprNode() {
    return peek().content == "typeof";
}
bool Parser::isTypeExprNode() {
    return isBasicExprNode() || isFnTypeExprNode();
}

// parser

IndexOpNode* Parser::parseIndexOpNode() {
    if (peek().content == "[") {
        auto* node = new IndexOpNode;
        node->left = eat();
        if (!isAddExprNode()) {
            throw parser_error::UnexpectedTokenError("Add Expression", peek().line, peek().column);
        }
        node->index = parseAddExprNode();
        if (peek().content != "]") {
            throw parser_error::UnexpectedTokenError("']'", peek().line, peek().column);
        }
        node->right = eat();

        return node;
    }
    throw parser_error::UnexpectedTokenError("Index Op", peek().line, peek().column);
}
CallOpNode* Parser::parseCallOpNode() {
    if (peek().content == "(") {
        auto* node = new CallOpNode;
        node->left = eat();
        if (isWholeExprNode()) {
            node->factors.push_back(parseWholeExprNode());
            while (peek().content == ",") {
                node->seps.push_back(new CommaOpNode { eat() });
                node->factors.push_back(parseWholeExprNode());
            }
        }
        if (peek().content != ")") {
            throw parser_error::UnexpectedTokenError("')'", peek().line, peek().column);
        }
        node->right = eat();

        return node;
    }
    throw parser_error::UnexpectedTokenError("Calling Op", peek().line, peek().column);
}
MulExprNode::MulOpOption* Parser::parseMulExprOp() {
    auto* opt = new MulExprNode::MulOpOption;
    if (peek().content == "*") opt->mul_op = new MulOpNode{eat()};
    else if (peek().content == "/") opt->div_op = new DivOpNode {eat()};
    else {
        throw parser_error::UnexpectedTokenError("'/' or '*'", peek().line, peek().column);
    }
    return opt;
}
AddExprNode::AddOpOption* Parser::parseAddExprOp() {
    auto* opt = new AddExprNode::AddOpOption;
    if (peek().content == "+") opt->add_op = new AddOpNode{eat()};
    else if (peek().content == "-") opt->sub_op = new SubOpNode{eat()};
    else {
        throw parser_error::UnexpectedTokenError("'+' or '-'", peek().line, peek().column);
    }
    return opt;
}
CompareExprNode::CompareOpOption* Parser::parseCompareExprOp() {
    auto* opt = new CompareExprNode::CompareOpOption;
    if (peek().content == "==") opt->eq_op = new EqOpNode {eat()};
    else if (peek().content == "!=") opt->neq_op = new NeqOpNode {eat()};
    else if (peek().content == ">") opt->gt_op = new GtOpNode {eat()};
    else if (peek().content == ">=") opt->ge_op = new GeOpNode {eat()};
    else if (peek().content == "<") opt->lt_op = new LtOpNode {eat()};
    else if (peek().content == "<=") opt->le_op = new LeOpNode {eat()};
    else {
        throw parser_error::UnexpectedTokenError("'==', '!=', '<', '>', '<=' or '>='", peek().line, peek().column);
    }
    return opt;
}
LogicExprNode::LogicOpOption* Parser::parseLogicExprOp() {
    auto* opt = new LogicExprNode::LogicOpOption;
    if (peek().content == "&&") opt->logic_and_op = new LogicAndOpNode {eat()};
    else if (peek().content == "||") opt->logic_or_op = new LogicOrOpNode {eat()};
    else if (peek().content == "!") opt->logic_not_op = new LogicNotOpNode {eat()};
    else {
        throw parser_error::UnexpectedTokenError("'&&', '||' or '!'", peek().line, peek().column);
    }
    return opt;
}

PrimaryExprNode* Parser::parsePrimExprNode() {
    if (isPrimExprNode()) {
        auto* node = new PrimaryExprNode;
        auto* factor = new PrimaryExprNode::Factor;
        
        auto makeFactor = [&]() {
            factor = new PrimaryExprNode::Factor;
            if (peek().content == "(") {
                factor->left = eat();
                if (isWholeExprNode()) factor->expr = parseWholeExprNode();
                else {
                    throw parser_error::UnexpectedTokenError("Whole Expression", peek().line, peek().column);
                }
                if (peek().content == ")") factor->right = eat();
                else {
                    throw parser_error::UnexpectedTokenError("')'", peek().line, peek().column);
                }
            }
            else {
                factor->head = parseBasicExprNode();
            }
            return factor;
        };

        node->head = makeFactor();
        while (peek().content == ".") {
            node->ops.push_back(new GmemOpNode { eat() });
            node->factors.push_back(makeFactor());
        }

        return node;
    }
    throw parser_error::UnexpectedTokenError("Primary Expression", peek().line, peek().column);
}
BasicExprNode* Parser::parseBasicExprNode() {
    if (isBasicExprNode()) {
        auto* node = new BasicExprNode;
        auto* opt = new BasicExprNode::CallingOpOption;
        node->factor = eat();
        
        while (peek().content == "(" || peek().content == "[") {
            if (peek().content == "(") {
                opt->call_op = parseCallOpNode();
                node->ops.push_back(opt);
            }
            else if (peek().content == "[") {
                opt->index_op = parseIndexOpNode();
                node->ops.push_back(opt);
            }
        }

        return node;
    }
    throw parser_error::UnexpectedTokenError("Basic Expression", peek().line, peek().column);
}
MulExprNode* Parser::parseMulExprNode() {
    if (isMulExprNode()) {
        auto* node = new MulExprNode;
        node->head = parsePrimExprNode();
        while (isMulOpNode()) {
            node->ops.push_back(parseMulExprOp());
            node->factors.push_back(parsePrimExprNode());
        }
        return node;
    }
    throw parser_error::UnexpectedTokenError("Mul Expression", peek().line, peek().column);
}
AddExprNode* Parser::parseAddExprNode() {
    if (isAddExprNode()) {
        auto* node = new AddExprNode;
        node->head = parseMulExprNode();
        while (isAddOpNode()) {
            node->ops.push_back(parseAddExprOp());
            node->factors.push_back(parseMulExprNode());
        }
        return node;
    }
    throw parser_error::UnexpectedTokenError("Add Expression", peek().line, peek().column);
}
CompareExprNode* Parser::parseCompareExprNode() {
    if (isCompareExprNode()) {
        auto* node = new CompareExprNode;
        node->head = parseAddExprNode();
        while (isCompareOpNode()) {
            node->ops.push_back(parseCompareExprOp());
            node->factors.push_back(parseAddExprNode());
        }
        return node;
    }
    throw parser_error::UnexpectedTokenError("Compare Expression", peek().line, peek().column);
}
LogicExprNode* Parser::parseLogicExprNode() {
    if (isLogicExprNode()) {
        auto* node = new LogicExprNode;
        if (peek().content == "!") {
            node->ops.push_back(parseLogicExprOp());
            node->head = parseCompareExprNode();
        }
        else {
            node->head = parseCompareExprNode();
            while (isLogicOpNode()) {
                node->ops.push_back(parseLogicExprOp());
                node->factors.push_back(parseCompareExprNode());
            }
        }
        return node;
    }
    throw parser_error::UnexpectedTokenError("Mul Expression", peek().line, peek().column);
}
TypeofExprNode* Parser::parseTypeofExprNode() {
    auto* node = new TypeofExprNode;
    node->mark = eat();
    if (!isCallOpNode())
        throw parser_error::UnexpectedTokenError("'('", peek().line, peek().column);

    node->calling = parseCallOpNode();

    return node;
}
FunctionLikeExprNode* Parser::parseFunctionLikeExprNode() {
    auto* node = new FunctionLikeExprNode;
    if (isTypeofExprNode()) node->typeof_expr = parseTypeofExprNode();

    return node;
}
WholeExprNode* Parser::parseWholeExprNode() {
    auto* node = new WholeExprNode;
    if (isLogicExprNode()) node->logic_expr = parseLogicExprNode();
    else if (isFnLikeExprNode()) node->fnlike_expr = parseFunctionLikeExprNode();
    else if (isListLiteralExprNode()) node->list_expr = parseListLiteralExprNode();
    else if (isStructLiteralExprNode()) node->struct_expr = parseStructFlagOpNode();

    else node->add_expr = parseAddExprNode();

    return node;
}

StructFlagOpNode* Parser::parseStructFlagOpNode() {
    if (peek().content == "struct") {
        auto* node = new StructFlagOpNode;
        node->op = eat();
        if (peek().content == "[]")
            node->list_flag = new ListFlagOpNode{eat()};
        return node;
    }
    throw parser_error::UnexpectedTokenError("'struct'", peek().line, peek().column);
}

BasicTypeExprNode* Parser::parseBasicTypeExprNode() {
    if (isBasicTypeExprNode()) {
        auto* node = new BasicTypeExprNode;
        if (peek().content == "struct")
            node->struct_flag = parseStructFlagOpNode();

        if (peek().kind == lexer::TokenKind::Ident)
            node->basic_type = eat();
        else
            throw parser_error::UnexpectedTokenError("Identifier", peek().line, peek().column);

        if (peek().content == "[]") {
            if (node->struct_flag != nullptr)
                throw parser_error::SyntaxError("An identifier '" + node->basic_type->token->content + "' cannot be declared as an array type. Identifier '" + node->basic_type->token->content + "' is not a type", peek().line, peek().column);
            else
                node->list_flag = new ListFlagOpNode {eat()};
        }
        else if (peek().content == "&")
            node->ref_flag = new RefFlagOpNode {eat()};

        return node;
    }
    throw parser_error::UnexpectedTokenError("'struct' or a type name", peek().line, peek().column);
}
FnTypeExprNode* Parser::parseFnTypeExprNode() {
    if (isFnTypeExprNode()) {
        auto* node = new FnTypeExprNode;
        if (peek().content != "(")
            throw parser_error::UnexpectedTokenError("'('", peek().line, peek().column);
        node->bgn_sym = eat();
        while (isTypeExprNode()) {
            node->elements.push_back(parseTypeExprNode());
            if (peek().content != ",")
                throw parser_error::UnexpectedTokenError("','", peek().line, peek().column);
            else if (peek().content == ")") break;
            else
                node->seps.push_back(eat());
        }
        node->end_sym = eat();

        if (peek().content != "->")
            throw parser_error::UnexpectedTokenError("'->'", peek().line, peek().column);
        node->ret_pointer = eat();
        if (!isTypeExprNode())
            throw parser_error::UnexpectedTokenError("TypeExpr", peek().line, peek().column);
        node->ret_type = parseTypeExprNode();
    }
    throw parser_error::UnexpectedTokenError("'fn'", peek().line, peek().column);
}
TypeExprNode* Parser::parseTypeExprNode() {
    auto* node = new TypeExprNode;
    if (isBasicExprNode()) {
        node->basic_type = parseBasicTypeExprNode();
        return node;
    }
    else if (isFnTypeExprNode()) {
        node->fn_type = parseFnTypeExprNode();
        return node;
    }
    else throw parser_error::UnexpectedTokenError("BasicTypeExpr, TupleTypeExpr or FnTypeExpr", peek().line, peek().column);
}

ListLiteralExprNode *Parser::parseListLiteralExprNode() {
    auto* node = new ListLiteralExprNode;
    if (peek().content == "mutable") node->mut_mark = eat();
    node->bgn = eat();
    while (isWholeExprNode()) {
        node->elements.push_back(parseWholeExprNode());
        if (peek().content != ",") break;
        node->seps.push_back(eat());
    }
    if (peek().content != "]")
        throw parser_error::UnexpectedTokenError("']'", peek().line, peek().column);
    node->end = eat();
    return node;
}

StructLiteralExprNode *Parser::parseStructLiteralExprNode() {
    auto* node = new StructLiteralExprNode;
    node->bgn =eat();
    while (true) {
        auto* tempPair = new StructLiteralExprNode::KeyPair;

        if (peek().kind != lexer::TokenKind::Ident)
            throw parser_error::UnexpectedTokenError("Identifier", peek().line, peek().column);
        tempPair->key = eat();
        if (peek().content != ":")
            throw parser_error::UnexpectedTokenError("':'", peek().line, peek().column);
        tempPair->rest = new RestOpNode{eat()};
        if (!isWholeExprNode())
            throw parser_error::UnexpectedTokenError("WholeExpr", peek().line, peek().column);
        tempPair->value = parseWholeExprNode();

        node->pairs.push_back(tempPair);

        if (peek().content != ",") break;
        node->seps.push_back(eat());
    }
    if (peek().content != "}")
        throw parser_error::UnexpectedTokenError("'}'", peek().line, peek().column);
    node->end = eat();

    return node;
}

AssignExprNode *Parser::parseAssignExprNode() {
    auto* node = new AssignExprNode;
    if (!isPrimExprNode())
        throw parser_error::UnexpectedTokenError("PrimaryExpr", peek().line, peek().column);
    node->lval = parsePrimExprNode();
    if (peek().content != "=")
        throw parser_error::UnexpectedTokenError("PrimaryExpr", peek().line, peek().column);
    node->op = new AssignOpNode {eat()};
    if (!isWholeExprNode())
        throw parser_error::UnexpectedTokenError("WholeExpr", peek().line, peek().column);
    node->rval = parseWholeExprNode();

    return node;
}

