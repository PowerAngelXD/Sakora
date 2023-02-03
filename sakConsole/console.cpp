//
// Created by BALL on 2023/2/2.
//

#include "console.h"

using namespace sakConsole;

void sakConsole::start() {
    std::cout<<welcomeText<<std::endl;
    std::string input;
    try {
        std::cout<<">>"<<std::endl;
        std::getline(std::cin, input);

    }
    catch (...) {

    }
}