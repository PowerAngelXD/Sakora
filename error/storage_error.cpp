//
// Created by BALL on 2022/12/28.
//

#include "storage_error.h"

storage_error::DuplicateIdentifierError::DuplicateIdentifierError(std::string src, int ln, int col) : ErrorBasic(src, ln, col) {}

void storage_error::DuplicateIdentifierError::printError() {
    ERROR_HEAD_DISPLAY
    std::cout<<"DuplicateIdentifier Error"<<std::endl;
    std::cout<<"    Attempt to create an existing identifier: '"<<source<<"' under the current scope"<<std::endl;
    std::cout<<"At line: "<<line<<"; column: "<<column<<std::endl;
}

storage_error::UnknownIdentifierError::UnknownIdentifierError(std::string src, int ln, int col) : ErrorBasic(src, ln, col) {}

void storage_error::UnknownIdentifierError::printError() {
    ERROR_HEAD_DISPLAY
    std::cout<<"UnknownIdentifier Error"<<std::endl;
    std::cout<<"    Unable to find an identifier named: '"<<source<<"' in the current scope or all its parent scopes"<<std::endl;
    std::cout<<"At line: "<<line<<"; column: "<<column<<std::endl;
}
