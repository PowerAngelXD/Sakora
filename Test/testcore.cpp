//
// Created by BALL on 2023/4/15.
//

#include "testcore.h"

sakTest::SakAssertError::SakAssertError(std::string c): content(c) {}

std::string sakTest::SakAssertError::what() {
    return content;
}

void sakTest::sakAssert(bool expr, std::string msg) {
    if (!expr) throw SakAssertError(msg);
}
void sakTest::debug(bool expr, std::string msg) {
    try {
        sakAssert(expr, msg);
    }
    catch (SakAssertError& e) {
        std::cout<<"Sakora-Inside Test\n"<<"Failed: "<<e.what()<<std::endl;
    }

    std::cout<<"Sakora-Inside Test\n"<<"Passed"<<std::endl;
}