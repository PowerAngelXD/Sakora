//
// Created by BALL on 2023/4/15.
//

#ifndef SAKORA_TESTCORE_H
#define SAKORA_TESTCORE_H

#include <iostream>

namespace sakTest {
    class SakAssertError: public std::exception {
        using std::exception::what;
    protected:
        std::string content;
        int line = 0, column = 0;
    public:
        explicit SakAssertError(std::string c);

        std::string what();
    };

    void sakAssert(bool expr, std::string msg);
    void debug(bool expr, std::string msg);
}

#endif //SAKORA_TESTCORE_H
