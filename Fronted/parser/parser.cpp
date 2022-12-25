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
    return peek().content == "*" || peek().content == "/";
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
    if (!isBasicExpressionNode()) {exit(6);}
    // definition part
    Node node(NodeKind::BasicExpression, eat()); // eat head
    node.childs.emplace_back(NodeKind::BasicExpression); // factors => childs[0]
    node.childs.emplace_back(NodeKind::BasicOp); // ops => childs[1]
    // generation part
    while (isBasicOpNode()) {
        node[1].childs.emplace_back(parseBasicOpNode());
        node[0].childs.emplace_back(NodeKind::BasicExpression, eat());
    }

    return node;
}
parser::Node parser::Parser::parseBasicOpNode() {
    if (!isBasicOpNode()) {exit(6);} // TODO: WILL ERROR

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
     if (!isMulExpressionNode()) {exit(6);}
     Node node(NodeKind::MulExpression);
     node.childs.emplace_back(NodeKind::BasicExpression); // head => childs[0]
     node.childs.emplace_back(NodeKind::MulOp); // ops => childs[1]
     node.childs.emplace_back(NodeKind::BasicExpression); // factors => childs[2]

     node.childs[0].childs.push_back(parseBasicExpressionNode());
     while (isMulOpNode()) {
         node[1].childs.push_back(parseMulOpNode());
         node[2].childs.push_back(parseBasicExpressionNode());
     }

     return node;
}
parser::Node parser::Parser::parseMulOpNode() {
    if (!isMulOpNode()) {exit(6);}

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
    if (!isAddExpressionNode()) {exit(6);}

    Node node(NodeKind::AddExpression);
    node.childs.emplace_back(NodeKind::MulExpression); // head => childs[0]
    node.childs.emplace_back(NodeKind::AddOp); // ops => childs[1]
    node.childs.emplace_back(NodeKind::MulExpression); // factors => childs[2]

    node.childs[0].childs.push_back(parseMulExpressionNode());
    while (isAddOpNode()) {
        node[1].childs.push_back(parseAddOpNode());
        node[2].childs.push_back(parseMulExpressionNode());
    }

    return node;
}
parser::Node parser::Parser::parseAddOpNode() {
    if (!isAddOpNode()) {exit(6);}

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