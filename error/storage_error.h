//
// Created by BALL on 2022/12/28.
//

#ifndef SAKORA_STORAGE_ERROR_H
#define SAKORA_STORAGE_ERROR_H

#include "error.h"
#include <vector>

namespace storage_error {
    struct DuplicateIdentifierError: error::ErrorBasic {
       DuplicateIdentifierError(std::string src, int ln, int col);

        void printError() override;
    };

    struct UnknownIdentifierError: error::ErrorBasic {
        UnknownIdentifierError(std::string src, int ln, int col);

        void printError() override;
    };

    const std::string get_chosen_type_val_mode = "chosentype";
    const std::string structure_mode = "structure";
    const std::string type_equal_mode = "tyequ";
    struct UnsupportedOperationError: error::ErrorBasic {
        UnsupportedOperationError(std::string src, int ln, int col);

        void printError() override;
    };
}

#endif //SAKORA_STORAGE_ERROR_H
