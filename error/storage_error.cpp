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

storage_error::UnsupportedOperationError::UnsupportedOperationError(std::string src, int ln, int col): ErrorBasic(src, ln, col) {}

void storage_error::UnsupportedOperationError::printError() {
    if (source == structure_mode) {
        ERROR_HEAD_DISPLAY
        std::cout<<"UnsupportedOperation Error"<<std::endl;
        std::cout<<"    Cannot perform operations between structures when overloaded operators are defined"<<std::endl;
        std::cout<<"At line: "<<line<<"; column: "<<column<<std::endl;
    }
    else if (source == type_equal_mode) {
        ERROR_HEAD_DISPLAY
        std::cout<<"UnsupportedOperation Error"<<std::endl;
        std::cout<<"    The precondition for any Boolean operation is that both types are the same (Only '==' and '!=' operators has this provision)"<<std::endl;
        std::cout<<"At line: "<<line<<"; column: "<<column<<std::endl;
    }
    else {
        std::vector<std::string> contents;
        std::string temp;
        for (char ch: source) {
            if (ch != '@') temp += ch;
            else {
                contents.push_back(temp);
                temp.clear();
            }
        }

        ERROR_HEAD_DISPLAY
        std::cout<<"UnsupportedOperation Error"<<std::endl;
        if (contents.size() == 3)
            std::cout<<"    Cannot perform: '"<<contents[0]<<"' operation between types: '"<<contents[1]<<"' and '"<<contents[2]<<"'"<<std::endl;
        else if (contents.size() == 2)
            std::cout<<"    Cannot perform: '"<<contents[0]<<"' operation with type: '"<<contents[1]<<std::endl;
        std::cout<<"At line: "<<line<<"; column: "<<column<<std::endl;
    }
}
