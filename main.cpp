#include "Backend/scope/value.h"
#include "sakVM/vm.h"


int main() {
    lexer::Lexer lex("3 != 4 && 1 == 2");
    lex.generate();

    parser::Parser p(lex.out);
    try {
        auto node = p.parseBooleanExpressionNode();
        visitor::Visitor vr(node);
        vr.visitBooleanExpression(node);

        sakVM vm(vr.constantPool, node[parser::Marker::head][0].token.line, node[parser::Marker::head][0].token.column);
        vm.threads.push_back(vr.out);
        vm.vm_run(0);

        auto result = vm.env.pop();
        std::cout<<*(bool*)(result.val())<<std::endl;
    }
    catch (parser_error::UnexpectedTokenError& e) {
        e.printError();
    }
    return 0;
}
