//
// Created by BALL on 2022/12/7.
//

#include "lex.h"

using namespace lexer;

Lexer::Lexer(std::string src) {
    source = std::move(src);
}

char Lexer::next() {
    char ch = source[++ pos];
    if (ch == '\n') {
        column = 1;
        line ++;
    }
    else column ++;

    return ch;
}

char Lexer::peekNext() {
    return source[pos + 1];
}

void Lexer::back() {
    char ch = source[-- pos];
    if (ch == '\n') {
        column = 1;
        line --;
    }
    else column --;
}

Token Lexer::makeNumber() {
    char chk = source[pos];
    if (!isdigit(chk)) {}

    std::string content;
    bool _dot_check = false;
    for (; pos < source.size(); chk = next()) {
        if (isdigit(chk)) content.push_back(chk);
        else if (chk == '.' && !_dot_check) {
            _dot_check = true;
            content.push_back(chk);
        }
        else if (chk == '.' && _dot_check) {
            content.push_back(chk);
            throw lexer_error::NotCorrectNumberError(content, line, column);
        }
        else break;
    }
    back();

    return {TokenKind::Number, content, line, column};
}

Token Lexer::makeIdentifier() {
    char chk = source[pos];
    if (!isalpha(chk)) {}

    std::string content;
    for(; pos < source.size(); chk = next()) {
        if (isalpha(chk) || isdigit(chk) || chk == '_') content.push_back(chk);
        else break;
    }
    back();

    if (content == "true" || content == "false") {
        return {
                TokenKind::Boolean,
                content,
                line,
                column
        };
    }
    else {
        return {
                is_keyword(content)?TokenKind::Keyword:TokenKind::Ident,
                content,
                line,
                column
        };
    }
}

Token Lexer::makeSymbol() {
    char chk = source[pos];
    if (!is_symbol_char(chk)) {
        throw lexer_error::IllegalSymbolError(std::to_string(chk), line, column);
    }
    if (chk == '+') {
        if (source[pos + 1] == '=') { pos ++; return {TokenKind::Symbol, "+=", line, column}; }
        else if (source[pos + 1] == '+') { pos ++; return {TokenKind::Symbol, "++", line, column}; }
        else return {TokenKind::Symbol, "+", line, column};
    }
    else if (chk == '-') {
        if (source[pos + 1] == '=') { pos ++; return {TokenKind::Symbol, "-=", line, column}; }
        else if (source[pos + 1] == '-') { pos ++; return {TokenKind::Symbol, "--", line, column}; }
        else return {TokenKind::Symbol, "-", line, column};
    }
    else if (chk == '*') {
        if (source[pos + 1] == '=') { pos ++; return {TokenKind::Symbol, "*=", line, column}; }
        else return {TokenKind::Symbol, "*", line, column};
    }
    else if (chk == '/') {
        if (source[pos + 1] == '=') { pos ++; return {TokenKind::Symbol, "/=", line, column}; }
        else return {TokenKind::Symbol, "/", line, column};
    }
    else if (chk == '=') {
        if (source[pos + 1] == '=') { pos ++; return {TokenKind::Symbol, "==", line, column}; }
        else return {TokenKind::Symbol, "=", line, column};
    }
    else if (chk == '!') {
        if (source[pos + 1] == '=') { pos ++; return {TokenKind::Symbol, "!=", line, column}; }
        else return {TokenKind::Symbol, "!", line, column};
    }
    else if (chk == '<') {
        if (source[pos + 1] == '=') { pos ++; return {TokenKind::Symbol, "<=", line, column}; }
        else return {TokenKind::Symbol, "<", line, column};
    }
    else if (chk == '>') {
        if (source[pos + 1] == '=') { pos ++; return {TokenKind::Symbol, ">=", line, column}; }
        else return {TokenKind::Symbol, ">", line, column};
    }
    else if (chk == '(') return {TokenKind::Symbol, "(", line, column};
    else if (chk == '[') {
        if (source[pos + 1] == ']') { pos ++; return {TokenKind::Symbol, "[]", line, column}; }
        else return {TokenKind::Symbol, "[", line, column};
    }
    else if (chk == ')') return {TokenKind::Symbol, ")", line, column};
    else if (chk == ']') return {TokenKind::Symbol, "]", line, column};
    else if (chk == '{') return {TokenKind::Symbol, "{", line, column};
    else if (chk == '}') return {TokenKind::Symbol, "}", line, column};
    else {
        throw lexer_error::IllegalSymbolError(std::to_string(chk), line, column);
    }
}

Token Lexer::makeString() {
    char chk = source[pos];
    if (chk != '"') {}

    std::string content;
    chk = next();
    for (; pos < source.size(); chk = next()) {
        if (chk != '"' && pos >= source.size() - 1) {
            throw lexer_error::StringUnCloseError(content, line, column);
        }

        if (chk == '"') break;
        else content.push_back(chk);
    }

    return {TokenKind::String, content, line, column};
}

void Lexer::makeComment() {
    char chk = source[pos];

    std::string debug;
    for (; pos < source.size(); chk = next()) {
        if (chk == '\n') break;
        debug.push_back(next());
    }
    next();
}

void Lexer::make(char chk) {
    if (chk == ' ' || chk == '\0') return;
    if (chk == '/' && source[pos + 1] == '/') {
        makeComment();
        return;
    }

    if (isdigit(chk)) out.push_back(makeNumber());
    else if (isalpha(chk) || chk == '_') out.push_back(makeIdentifier());
    else if (is_symbol_char(chk)) out.push_back(makeSymbol());
    else if (chk == '"') out.push_back(makeString());
    else {
        std::string src = std::string();
        src.push_back(chk);
        throw lexer_error::IllegalSymbolError(src, line, column + 1);
    }
}

void Lexer::generate() {
    char chk = source[pos];
    for (; pos < source.size(); chk = next()) {
        make(chk);
    }
    out.emplace_back(TokenKind::Eof, "EOF", -1, -1);
}

