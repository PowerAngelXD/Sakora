//
// Created by BALL on 2022/12/23.
//

#include "parser.h"

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
            node->factors->push_back(parseWholeExprNode());
            while (peek().content == ",") {
                node->seps->push_back(new CommaOpNode { eat() });
                node->factors->push_back(parseWholeExprNode());
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
MulExprNode::MulOption* Parser::parseMulExprOp() {
    auto* opt = new MulExprNode::MulOption;
    if (peek().content == "*") { 
        TG(MulExprNode::MulOp, *opt) = new MulOpNode { eat() };
        return opt;
    }
    else if (peek().content == "/") { 
        TG(MulExprNode::DivOp, *opt) = new DivOpNode { eat() };
        return opt;
    }
    else {
        throw parser_error::UnexpectedTokenError("'/' or '*'", peek().line, peek().column);
    }
}
AddExprNode::AddOption* Parser::ParseAddExprOp() {
    auto* opt = new AddExprNode::AddOption;
    if (peek().content == "+") { 
        TG(AddExprNode::AddOp, *opt) = new AddOpNode { eat() };
        return opt;
    }
    else if (peek().content == "-") { 
        TG(AddExprNode::SubOp, *opt) = new SubOpNode { eat() };
        return opt;
    }
    else {
        throw parser_error::UnexpectedTokenError("'+' or '-'", peek().line, peek().column);
    }
}
CompareExprNode::CompareOption* Parser::parseCompareExprOp() {
    auto* opt = new CompareExprNode::CompareOption;
    if (peek().content == "==") { 
        TG(CompareExprNode::EqOp, *opt) = new EqOpNode { eat() };
        return opt;
    }
    else if (peek().content == "!=") { 
        TG(CompareExprNode::NeqOp, *opt) = new NeqOpNode { eat() };
        return opt;
    }
    else if (peek().content == ">") { 
        TG(CompareExprNode::GtOp, *opt) = new GtOpNode { eat() };
        return opt;
    }
    else if (peek().content == ">=") { 
        TG(CompareExprNode::GeOp, *opt) = new GeOpNode { eat() };
        return opt;
    }
    else if (peek().content == "<") { 
        TG(CompareExprNode::LtOp, *opt) = new LtOpNode { eat() };
        return opt;
    }
    else if (peek().content == "<=") { 
        TG(CompareExprNode::LeOp, *opt) = new LeOpNode { eat() };
        return opt;
    }
    else {
        throw parser_error::UnexpectedTokenError("'==', '!=', '<', '>', '<=' or '>='", peek().line, peek().column);
    }
}
LogicExprNode::LogicOption* Parser::parseLogicExprOp() {
    auto* opt = new LogicExprNode::LogicOption;
    if (peek().content == "&&") { 
        TG(LogicExprNode::LogicAndOp, *opt) = new LogicAndOpNode { eat() };
        return opt;
    }
    else if (peek().content == "||") { 
        TG(LogicExprNode::LogicOrOp, *opt) = new LogicOrOpNode { eat() };
        return opt;
    }
    else if (peek().content == "!") { 
        TG(LogicExprNode::LogicNotOp, *opt) = new LogicNotOpNode { eat() };
        return opt;
    }
    else {
        throw parser_error::UnexpectedTokenError("'&&', '||' or '!'", peek().line, peek().column);
    }
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
            node->ops->push_back(new GmemOpNode { eat() });
            node->factors->push_back(makeFactor());
        }

        return node;
    }
}
BasicExprNode* Parser::parseBasicExprNode() {
    if (isBasicExprNode()) {
        auto* node = new BasicExprNode;
        node->factor = eat();
        
        while (peek().content == "(" || peek().content == "[") {
            if (peek().content == "(") {
                node->ops->push_back(new BasicExprNode::CallingOption { nullptr, parseCallOpNode() });
            }
            else if (peek().content == "[") {
                node->ops->push_back(new BasicExprNode::CallingOption { parseIndexOpNode(), nullptr });
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
            node->ops->push_back(parseMulExprOp());
            node->factors->push_back(parsePrimExprNode());
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
            node->ops->push_back(ParseAddExprOp());
            node->factors->push_back(parseMulExprNode());
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
            node->ops->push_back(parseCompareExprOp());
            node->factors->push_back(parseAddExprNode());
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
            node->ops->push_back(parseLogicExprOp());
            node->factors->push_back(parseCompareExprNode());
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

