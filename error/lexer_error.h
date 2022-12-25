//
// Created by BALL on 2022/12/7.
//

#ifndef EYON_LEXER_ERROR_H
#define EYON_LEXER_ERROR_H
#include "error.h"

namespace lexer_error {
    struct NotCorrectNumberError: public error::ErrorBasic {
        NotCorrectNumberError(std::string src, int ln, int col);

        void printError() override;
    };

    struct StringUnCloseError: public error::ErrorBasic {
        StringUnCloseError(std::string src, int ln, int col);

        void printError() override;
    };

    struct IllegalSymbolError: public error::ErrorBasic {
        IllegalSymbolError(std::string src, int ln, int col);

        void printError() override;
    };
}

#endif //EYON_LEXER_ERROR_H
