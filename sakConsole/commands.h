//
// Created by BALL on 2023/2/2.
//

#ifndef SAKORA_COMMANDS_H
#define SAKORA_COMMANDS_H

#include "../Backend/scope/value.h"
#include "../sakVM/vm.h"

namespace sakConsole {
    static std::string helpText = "Unknown Content";

    std::vector<std::string> commandSpliter(std::string src, char sep);

    typedef std::vector<std::string> CommandArgv;

    void cmdHelp();
    void cmdRepl();
}

#endif //SAKORA_COMMANDS_H
