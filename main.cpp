#include "Backend/scope/value.h"
#include "sakVM/vm.h"


int main() {
    lexer::Lexer lex("3+2");
    lex.generate();

    parser::Parser p(lex.out);
    try {
        auto node = p.parseAddExprNode();
        visitor::Visitor vr;
        vr.visitAddExpression(node);

        sakVM vm(vr.constantPool, vr.out[0].ln, vr.out[0].col);
        vm.threads.push_back(vr.out);
        vm.vm_run(0);

        std::cout<<*(long long*)vm.env.pop().val()<<std::endl;
    }
    catch (parser_error::UnexpectedTokenError& e) {
        e.printError();
    }
    return 0;
}
