//
// Created by BALL on 2022/12/7.
//

#include "lexer_error.h"

#include <utility>

lexer_error::NotCorrectNumberError::NotCorrectNumberError(std::string src, int ln, int col) :
    ErrorBasic(std::move(src), ln, col) {}

void lexer_error::NotCorrectNumberError::printError() {
    ERROR_HEAD_DISPLAY
    std::cout<<"NotCorrectNumberError Error"<<std::endl;
    std::cout<<"    Provide the number text: '"<<source<<"' is not a correct number format!"<<std::endl;
    std::cout<<"At line: "<<line<<"; column: "<<column<<std::endl;
}

//

lexer_error::StringUnCloseError::StringUnCloseError(std::string src, int ln, int col) :
    ErrorBasic(std::move(src), ln, col) {}

void lexer_error::StringUnCloseError::printError() {
    ERROR_HEAD_DISPLAY
    std::cout<<"StringUnClose Error"<<std::endl;
    std::cout<<"    String text: '"<<source<<"' is not closed!"<<std::endl;
    std::cout<<"At line: "<<line<<"; column: "<<column<<std::endl;
}

//

lexer_error::IllegalSymbolError::IllegalSymbolError(std::string src, int ln, int col) :
        ErrorBasic(std::move(src), ln, col) {}

void lexer_error::IllegalSymbolError::printError() {
    ERROR_HEAD_DISPLAY
    std::cout<<"IllegalSymbol Error"<<std::endl;
    std::cout<<"    Illegal text: '"<<source<<"' !"<<std::endl;
    std::cout<<"At line: "<<line<<"; column: "<<column<<std::endl;
}

