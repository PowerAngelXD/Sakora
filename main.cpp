#include "Backend/scope/value.h"
#include "sakVM/vm.h"


int main() {
    lexer::Lexer lex("1+5*4+3/3");
    lex.generate();

    parser::Parser p(lex.out);
    auto node = p.parseAddExpressionNode();

    visitor::Visitor vr(node);
    vr.visitAddExpression(node);

    sakVM vm(vr.constantPool, node[parser::Marker::head][0].token.line, node[parser::Marker::head][0].token.column);
    vm.threads.push_back(vr.out);
    vm.vm_run(0);

    auto result = vm.env.pop();
    std::cout<<*(int*)(result.val())<<std::endl;
    return 0;
}
