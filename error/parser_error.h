//
// Created by BALL on 2022/12/26.
//

#ifndef SAKORA_PARSER_ERROR_H
#define SAKORA_PARSER_ERROR_H
#include "error.h"

namespace parser_error {
    struct UnexpectedTokenError: public error::ErrorBasic {
        UnexpectedTokenError(std::string src, int ln, int col);

        void printError() override;
    };
}

#endif //SAKORA_PARSER_ERROR_H
