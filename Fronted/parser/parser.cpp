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
    return peek().kind != lexer::TokenKind::NullToken;
}
bool Parser::isBasicOpNode() {
    return peek().content == ".";
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
    return isCompareExprNode();
}
bool Parser::isLogicOpNode() {
    return peek().content == "||" || peek().content == "&&" || peek().content == "!";
}
bool Parser::isWholeExprNode() {
    return isAddExprNode() || isLogicExprNode();
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
        if (!isWholeExprNode()) {
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
    throw parser_error::UnexpectedTokenError("Mul Expression", peek().line, peek().column);
}
LogicExprNode* Parser::parseLogicExprNode() {
    if (isMulExprNode()) {
        auto* node = new LogicExprNode;
        node->head = parseCompareExprNode();
        while (isLogicOpNode()) {
            node->ops.push_back(parseLogicExprOp());
            node->factors.push_back(parseCompareExprNode());
        }
        return node;
    }
    throw parser_error::UnexpectedTokenError("Mul Expression", peek().line, peek().column);
}
WholeExprNode* Parser::parseWholeExprNode() {
    auto* node = new WholeExprNode;
    if (isAddExprNode()) node->add_expr = parseAddExprNode();
    else if (isLogicExprNode()) node->logic_expr = parseLogicExprNode();

    return node;
}

