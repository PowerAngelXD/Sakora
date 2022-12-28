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
    for (; temp < token_group.size(); temp ++) {
        if (peek().kind == lexer::Symbol && isCompareOpNode()) { return true; }
    }
    return false;
}
bool parser::Parser::isCompareOpNode() {
    return peek().content == "==" || peek().content == "!=" ||
           peek().content == ">=" || peek().content == "<=" ||
           peek().content == ">" || peek().content == "<";
}
bool parser::Parser::isBooleanExpressionNode() {
    auto temp = pos;
    for (; temp < token_group.size(); temp ++) {
        if (peek().kind == lexer::Symbol && isBooleanOpNode()) { return true; }
    }
    return false;
}
bool parser::Parser::isBooleanOpNode() {
    return peek().content == "||" || peek().content == "&&" || peek().content == "!";
}
bool parser::Parser::isWholeExpressionNode() {
    return isAddExpressionNode() || isBooleanExpressionNode();
}

// parser

parser::Node parser::Parser::parseBasicExpressionNode() {
    /**
     * BasicExpressionNode {
     *      Token head;
     *      vector<BasicOpNode> ops;
     *      vector<Token> factors;
     * }
     */
     // checker part
    if (!isBasicExpressionNode()) {
        throw parser_error::UnexpectedTokenError("<Token>", token_group[pos].line, token_group[pos].column);
    }
    // definition part
    Node node(NodeKind::BasicExpression); // eat head
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
    /**
     * MulExpressionNode {
     *      BasicExpressionNode head;
     *      vector<MulOpNode> ops;
     *      vector<BasicExpressionNode> factors;
     * }
     */
     if (!isMulExpressionNode()) {
         throw parser_error::UnexpectedTokenError("PrimaryExpression", token_group[pos].line, token_group[pos].column);
     }
     Node node(NodeKind::MulExpression);
     node.subs.emplace_back(NodeKind::BasicExpression); // head => subs[0]
     node.subs.emplace_back(NodeKind::MulOp); // ops => subs[1]
     node.subs.emplace_back(NodeKind::BasicExpression); // factors => subs[2]

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
    /**
     * AddExpressionNode {
     *      MulExpressionNode head;
     *      vector<AddOpNode> ops;
     *      vector<MulExpressionNode> factors;
     * }
     */
    if (!isAddExpressionNode()) {
        throw parser_error::UnexpectedTokenError("Mul Expression", token_group[pos].line, token_group[pos].column);
    }

    Node node(NodeKind::AddExpression);
    node.subs.emplace_back(NodeKind::MulExpression); // head => subs[0]
    node.subs.emplace_back(NodeKind::AddOp); // ops => subs[1]
    node.subs.emplace_back(NodeKind::MulExpression); // factors => subs[2]

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
//parser::Node parser::Parser::parseCompareExpressionNode() {
//
//}
//parser::Node parser::Parser::parseCompareOpNode() {
//
//}
//parser::Node parser::Parser::parseBooleanExpressionNode() {
//
//}
//parser::Node parser::Parser::parseBooleanOpNode() {
//
//}