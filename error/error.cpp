//
// Created by BALL on 2022/12/7.
//

#include "error.h"

error::ErrorBasic::ErrorBasic(std::string src, int ln, int col):
    source(src), line(ln), column(col) {}

std::string error::ErrorBasic::what() {
    return source;
}

std::tuple<int, int> error::ErrorBasic::getLineCol() {
    return {line, column};
}

void error::ErrorBasic::printError() {
    std::cout<<"Error: "<<std::endl;
    std::cout<<source<<std::endl;
    std::cout<<"line: "<<line<<"; column: "<<column<<std::endl;
}
