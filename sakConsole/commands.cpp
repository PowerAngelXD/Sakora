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

        try {
            lexer::Lexer lex(repl_text);
            lex.generate();

            parser::Parser p(lex.out);

            auto node = p.parseWholeExprNode();
            visitor::Visitor vr;
            vr.visitWholeExpression(node);

            sakVM vm(vr.constantPool, vr.out[0].ln, vr.out[0].col);
            vm.threads.push_back(vr.out);
            vm.vm_run(0);

            auto result = vm.env.pop();
            if (result.getType().type_content[0].unit_type->basic == type::Integer)
                std::cout<<*(long long*)result.val()<<std::endl;
            else
                std::cout<<*(double*)result.val()<<std::endl;
        }
        catch (parser_error::UnexpectedTokenError& e) {e.printError();}
        catch (parser_error::SyntaxError& e) {e.printError();}
        catch (lexer_error::IllegalSymbolError& e) {e.printError();}
        catch (lexer_error::StringUnCloseError& e) {e.printError();}
        catch (lexer_error::NotCorrectNumberError& e) {e.printError();}
        catch (storage_error::UnsupportedOperationError& e) {e.printError();}
        catch (storage_error::UnknownIdentifierError& e) {e.printError();}
        catch (storage_error::DuplicateIdentifierError& e) {e.printError();}
    }
}