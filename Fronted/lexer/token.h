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
                                                "if", "else", "import", "typeof", "fn"};
    bool is_keyword(const std::string& str);

    static std::vector<char> symbols = {'=', '+', '-', '/', '*', 
                                        ',', '.', '?', ':', '|', 
                                        '!', '%', '^', '&', '=', 
                                        '@', ';', '(', ')', '[',
                                        ']', '{', '}', '<', '>'};
    bool is_symbol_char(char ch);

    // Enumeration of token kinds
    enum TokenKind {
        Number,   // number literal
        Boolean,  // boolean literal
        String,   // string literal
        Ident,    // identifier
        Keyword,  // keyword
        Symbol,   // symbol
        Eof,      // end of file
        NullToken // null token
    };

    // Convert a TokenKind to a string
    std::string kind_to_string(TokenKind kind);

    // Struct representing a token
    struct Token {
        TokenKind kind = TokenKind::NullToken; // kind of the token
        std::string content = "NullToken";      // content of the token
        int line = 1;                           // line number of the token in the source code
        int column = 1;                         // column number of the token in the source code

        // Constructor

        // construct with kind, content, line number, and column number
        Token(TokenKind k, std::string c, int ln, int col);
        Token() = default;

        // Comparison operators

        // check if two tokens are equal
        bool operator ==(const Token& tok) const;
        // check if two tokens are not equal
        bool operator !=(const Token& tok) const;

        // Convert the token to a string
        [[nodiscard]] std::string to_string() const;
    };

    static Token null_token = {TokenKind::NullToken, "NullToken", -1, -1};

    typedef std::vector<Token> TokenGroup;
}

#endif //SAKORA_TOKEN_H
