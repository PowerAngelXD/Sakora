//
// Created by BALL on 2023/2/2.
//

#include "commands.h"

using namespace sakConsole;

std::vector<std::string> sakConsole::commandSpliter(std::string src, char sep) {
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

void sakConsole::cmdHelp() {
    std::cout<<helpText<<std::endl;
}
void sakConsole::cmdRepl() {
    std::cout<<"Now the console enters the REPL mode. If you want to exit, please enter '.quit'"<<std::endl;
    std::string repl_text;
    while (true) {
        std::cout<<"input >";
        std::getline(std::cin, repl_text);

        if (repl_text == ".quit") break;


        try {
            lexer::Lexer lex(repl_text);
            lex.generate();

            parser::Parser p(lex.out);

            auto node = p.parseWholeExprNode();
            visitor::Visitor vr;
            vr.visitWholeExpression(node);

            saKVM vm(vr.constantPool, vr.out[0].ln, vr.out[0].col);
            vm.threads.push_back(vr.out);
            vm.run(0);

            auto result = vm.env.pop();
            result.debugPrint(false);
        }
        SAK_PARSER_ERROR_CATCH
        SAK_STORAGE_ERROR_CATCH
    }
}