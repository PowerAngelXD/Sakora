//
// Created by BALL on 2022/12/7.
//

#ifndef SAKORA_TOKEN_H
#define SAKORA_TOKEN_H
#include <iostream>
#include <string>
#include <vector>

namespace lexer {
    static std::vector<std::string> keywords = {"let", "if", "dynic", "static", "repeat", "loop", "until", "while", "for",
                                                "if", "else", "import", "typeof"};
    bool is_keyword(const std::string& str);

    static std::vector<char> symbols = {'=', '+', '-', '/', '*', 
                                        ',', '.', '?', ':', '|', 
                                        '!', '%', '^', '&', '=', 
                                        '@', ';', '(', ')', '[',
                                        ']', '{', '}'};
    bool is_symbol_char(char ch);

    enum TokenKind {
        Number, String, Ident,
        Keyword, Symbol, Eof, NullToken
    };
    std::string kind_to_string(TokenKind kind);

    struct Token {
        TokenKind kind = TokenKind::NullToken;
        std::string content = "NullToken";
        int line = 1;
        int column = 1;

        Token(TokenKind k, std::string c, int ln, int col);
        Token()=default;
        bool operator ==(const Token& tok) const;
        bool operator !=(const Token& tok) const;

        [[nodiscard]] std::string to_string() const;
    };
    static Token null_token = {TokenKind::NullToken, "NullToken", -1, -1};

    typedef std::vector<Token> TokenGroup;
}

#endif //SAKORA_TOKEN_H
