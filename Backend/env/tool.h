//
// Created by BALL on 2022/12/31.
//

#ifndef SAKORA_TOOL_H
#define SAKORA_TOOL_H

#include <iostream>
#include <string>
#include <vector>

namespace sakVM_core {
    std::vector<std::string> splitStr(std::string src, char sep);
    std::string readFile(std::string path);
}

#endif //SAKORA_TOOL_H
