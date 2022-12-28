//
// Created by BALL on 2022/12/26.
//

#include "parser_error.h"

using namespace parser_error;

UnexpectedTokenError::UnexpectedTokenError(std::string src, int ln, int col): ErrorBasic(src, ln, col) {}

void UnexpectedTokenError::printError() {
    ERROR_HEAD_DISPLAY
    std::cout<<"UnexpectedToken Error"<<std::endl;
    std::cout<<"    Expect: "<<source<<", but it provides unexpected Token"<<std::endl;
    std::cout<<"At line: "<<line<<"; column: "<<column<<std::endl;
}
