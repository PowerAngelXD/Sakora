//
// Created by BALL on 2023/2/2.
//

#ifndef SAKORA_CONSOLE_H
#define SAKORA_CONSOLE_H

#include "commands.h"

namespace sakConsole {
    namespace ver {
        // Version of Sakora programming language
        static std::string releaseVersion = "Sakora Preview";
        // Version number during development
        static std::string devVersion = "dev-20230202-";
        // Version of Sakora Console
        static std::string consoleVersion = "0.1";
    }

    static std::string welcomeText = "Welcome to the SakoraConsole!\n"
                                     "You can type 'help' for the console help\n"
                                     "Type 'exit' to exit the console\n"
                                     "Console Current Version: " + ver::consoleVersion;

    // Console start!!!
    void start();
}

#endif //SAKORA_CONSOLE_H
