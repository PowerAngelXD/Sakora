//
// Created by BALL on 2022/12/31.
//

#include <fstream>
#include "tool.h"

using namespace sakVM_core;

std::vector<std::string> sakVM_core::splitStr(std::string src, char sep) {
    std::vector<std::string> ret;
    std::string temp;
    for (char ch: src) {
        if (ch != sep) temp += ch;
        else {
            ret.push_back(temp);
            temp.clear();
        }
    }
    return ret;
}
std::string sakVM_core::readFile(std::string path) {
    std::ifstream file(path);
    std::istreambuf_iterator<char> begin(file);
    std::istreambuf_iterator<char> end;

    return {begin, end};
}