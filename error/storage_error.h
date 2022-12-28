//
// Created by BALL on 2022/12/28.
//

#ifndef SAKORA_STORAGE_ERROR_H
#define SAKORA_STORAGE_ERROR_H

#include "error.h"

namespace storage_error {
    struct DuplicateIdentifierError: error::ErrorBasic {
       DuplicateIdentifierError(std::string src, int ln, int col);

        void printError() override;
    };

    struct UnknownIdentifierError: error::ErrorBasic {
        UnknownIdentifierError(std::string src, int ln, int col);

        void printError() override;
    };


}

#endif //SAKORA_STORAGE_ERROR_H
