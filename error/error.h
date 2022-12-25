//
// Created by BALL on 2022/12/7.
//

#ifndef EYON_ERROR_H
#define EYON_ERROR_H
#include <iostream>
#include <string>
#include <tuple>

#define ERROR_HEAD_DISPLAY std::cout<<"An exception is thrown when the program is running:"<<std::endl;

namespace error {
class ErrorBasic: public std::exception {
protected:
        std::string source;
        int line = 0, column = 0;
    public:
        ErrorBasic(std::string src, int ln, int col);

        std::string what();
        std::tuple<int, int> getLineCol();

        virtual void printError();
    };
}

#endif //EYON_ERROR_H
