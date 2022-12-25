//
// Created by BALL on 2022/12/7.
//

#include "token.h"

#include <utility>

// TokenKind
std::string lexer::kind_to_string(lexer::TokenKind kind) {
    switch (kind) {
        case Number: return "Number"; break;
        case String: return "String"; break;
        case Ident: return "Identifier"; break;
        case Keyword: return "Keyword"; break;
        case Symbol: return "Symbol"; break;
        case Eof: return "Eof"; break;
        case NullToken: return "NullToken"; break;
        default: return "null";
    }
}

// Keywords
bool lexer::is_keyword(const std::string& str) {
    for (const auto& s: keywords) {
        if (str == s) return true;
    }
    return false;
}

// Symbols
bool lexer::is_symbol_char(char ch) {
    for (auto c: symbols) {
        if (ch == c) return true;
    }
    return false;
}

// Token
lexer::Token::Token(TokenKind k, std::string c, int ln, int col) :
    kind(k), content(c), line(ln), column(col) {}

bool lexer::Token::operator ==(const Token& tok) const {
    return content == tok.content && kind == tok.kind;
}

bool lexer::Token::operator !=(const Token& tok) const {
    return content != tok.content && kind != tok.kind;
}

std::string lexer::Token::to_string() const {
    std::string ret = "Token: {";
    ret += "c: " + content + ", ";
    ret += "k: " + kind_to_string(kind) + ", ";
    ret += "ln: " + std::to_string(line) + ", ";
    ret += "col: " + std::to_string(column) + "}";
    return ret;
}
