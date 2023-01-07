//
// Created by BALL on 2022/12/23.
//

#include "parser.h"

#include <utility>

parser::Parser::Parser(std::vector<lexer::Token> tg):
    token_group(std::move(tg)) {}

lexer::Token parser::Parser::peek(size_t offset) {
    return token_group[pos + offset];
}
lexer::Token parser::Parser::eat() {
    return token_group[pos ++];
}

// checker

bool parser::Parser::isBasicExpressionNode() {
    return peek().kind != lexer::TokenKind::NullToken;
}
bool parser::Parser::isBasicOpNode() {
    return peek().content == ".";
}
bool parser::Parser::isMulExpressionNode() {
    return isBasicExpressionNode();
}
bool parser::Parser::isMulOpNode() {
    return peek().content == "*" || peek().content == "/" || peek().content == "%";
}
bool parser::Parser::isAddExpressionNode() {
    return isMulExpressionNode();
}
bool parser::Parser::isAddOpNode() {
    return peek().content == "+" || peek().content == "-";
}
bool parser::Parser::isCompareExpressionNode() {
    auto temp = pos;
    if (isAddExpressionNode()) {
        parseAddExpressionNode(); // ignore the returned value
        if (isCompareOpNode()) { pos = temp; return true; }
        else { pos = temp; return false; }
    }
    return false;
}
bool parser::Parser::isCompareOpNode() {
    return peek().content == "==" || peek().content == "!=" ||
           peek().content == ">=" || peek().content == "<=" ||
           peek().content == ">" || peek().content == "<";
}
bool parser::Parser::isBooleanExpressionNode() {
    return isCompareOpNode();
}
bool parser::Parser::isBooleanOpNode() {
    return peek().content == "||" || peek().content == "&&" || peek().content == "!";
}
bool parser::Parser::isWholeExpressionNode() {
    return isAddExpressionNode() || isBooleanExpressionNode();
}

// parser

parser::Node parser::Parser::parseBasicExpressionNode() {
     // checker part
    if (!isBasicExpressionNode()) {
        throw parser_error::UnexpectedTokenError("<Token>", token_group[pos].line, token_group[pos].column);
    }
    // definition part
    Node node(NodeKind::Container); // eat head
    node.subs.emplace_back(NodeKind::BasicExpression); // head => subs[0]
    node.subs.emplace_back(NodeKind::BasicOp); // ops => subs[1]
    node.subs.emplace_back(NodeKind::BasicExpression); // factors => subs[2]

    node[Marker::head].subs.emplace_back(NodeKind::BasicExpression); // gen head
    node[Marker::head][0].token = eat();
    // generation part
    while (isBasicOpNode()) {
        node[Marker::ops].subs.emplace_back(parseBasicOpNode());
        node[Marker::factors].subs.emplace_back(NodeKind::BasicExpression, eat());
    }

    return node;
}
parser::Node parser::Parser::parseBasicOpNode() {
    if (!isBasicOpNode()) {
        throw parser_error::UnexpectedTokenError("'.'", token_group[pos].line, token_group[pos].column);
    }

    return {NodeKind::BasicOp, eat()};
}
parser::Node parser::Parser::parseMulExpressionNode() {
     if (!isMulExpressionNode()) {
         throw parser_error::UnexpectedTokenError("PrimaryExpression", token_group[pos].line, token_group[pos].column);
     }
     Node node(NodeKind::Container);
     node.subs.emplace_back(NodeKind::BasicExpression);
     node.subs.emplace_back(NodeKind::MulOp);
     node.subs.emplace_back(NodeKind::BasicExpression);

     node[Marker::head].subs.push_back(parseBasicExpressionNode());
     while (isMulOpNode()) {
         node[Marker::ops].subs.push_back(parseMulOpNode());
         node[Marker::factors].subs.push_back(parseBasicExpressionNode());
     }

     return node;
}
parser::Node parser::Parser::parseMulOpNode() {
    if (!isMulOpNode()) {
        throw parser_error::UnexpectedTokenError("'*', '/' or '%'", token_group[pos].line, token_group[pos].column);
    }

    return {NodeKind::MulOp, eat()};
}
parser::Node parser::Parser::parseAddExpressionNode() {
    if (!isAddExpressionNode()) {
        throw parser_error::UnexpectedTokenError("Mul Expression", token_group[pos].line, token_group[pos].column);
    }

    Node node(NodeKind::Container);
    node.subs.emplace_back(NodeKind::MulExpression);
    node.subs.emplace_back(NodeKind::AddOp);
    node.subs.emplace_back(NodeKind::MulExpression);

    node[Marker::head].subs.push_back(parseMulExpressionNode());
    while (isAddOpNode()) {
        node[Marker::ops].subs.push_back(parseAddOpNode());
        node[Marker::factors].subs.push_back(parseMulExpressionNode());
    }

    return node;
}
parser::Node parser::Parser::parseAddOpNode() {
    if (!isAddOpNode()) {
        throw parser_error::UnexpectedTokenError("'+' or '-'", token_group[pos].line, token_group[pos].column);
    }

    return {NodeKind::AddOp, eat()};
}
parser::Node parser::Parser::parseCompareExpressionNode() {
    if (!isCompareExpressionNode()) {
        throw parser_error::UnexpectedTokenError("Compare Expression", token_group[pos].line, token_group[pos].column);
    }

    Node node(NodeKind::Container);
    node.subs.emplace_back(NodeKind::AddExpression);
    node.subs.emplace_back(NodeKind::CompareOp);
    node.subs.emplace_back(NodeKind::AddExpression);

    node[Marker::head].subs.push_back(parseAddExpressionNode());
    while (isCompareOpNode()) {
        node[Marker::ops].subs.push_back(parseCompareOpNode());
        node[Marker::factors].subs.push_back(parseAddExpressionNode());
    }

    return node;
}
parser::Node parser::Parser::parseCompareOpNode() {
    if (!isCompareOpNode()) {
        throw parser_error::UnexpectedTokenError("'==', '!=', '<=', '>=', '<' or '>'", token_group[pos].line, token_group[pos].column);
    }

    return {NodeKind::CompareOp, eat()};
}
parser::Node parser::Parser::parseBooleanExpressionNode() {
    if (!isBooleanExpressionNode()) {
        throw parser_error::UnexpectedTokenError("Boolean Expression", token_group[pos].line, token_group[pos].column);
    }

    Node node(NodeKind::Container);
    node.subs.emplace_back(NodeKind::CompareExpression);
    node.subs.emplace_back(NodeKind::CompareOp);
    node.subs.emplace_back(NodeKind::CompareExpression);

    node[Marker::head].subs.push_back(parseCompareExpressionNode());
    while (isBooleanOpNode()) {
        node[Marker::ops].subs.push_back(parseBooleanOpNode());
        node[Marker::factors].subs.push_back(parseCompareExpressionNode());
    }

    return node;
}
parser::Node parser::Parser::parseBooleanOpNode() {
    if (!isBooleanOpNode()) {
        throw parser_error::UnexpectedTokenError("'||', '&&' or '!'", token_group[pos].line, token_group[pos].column);
    }

    return {NodeKind::BooleanOp, eat()};
}