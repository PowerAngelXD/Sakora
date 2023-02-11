//
// Created by BALL on 2022/12/7.
//

#ifndef SAKORA_LEX_H
#define SAKORA_LEX_H
#include "token.h"
#include "../../error/lexer_error.h"

namespace lexer {
    struct Lexer {
        Lexer()=default;
        explicit Lexer(std::string src);

        Token makeNumber();
        Token makeString();
        Token makeIdentifier();
        Token makeSymbol();
        void makeComment();

        void make(char chk);
        char next();
        char peekNext();
        void back();

        void generate();
        TokenGroup out;

    private:
        std::string source;
        size_t pos = 0;
        int column = 0, line = 1;
    };
}

#endif //SAKORA_LEX_H
