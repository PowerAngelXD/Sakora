#include "Backend/scope/value.h"
#include "sakVM/vm.h"


int main() {
    lexer::Lexer lex("3+2");
    lex.generate();

    parser::Parser p(lex.out);
    try {
        auto node = p.parseAddExprNode();
        //visitor::Visitor vr(node);
        //vr.visitAddExpression(node);

        //sakVM vm(vr.constantPool, node[parser::Marker::head][0].token.line, node[parser::Marker::head][0].token.column);
        //vm.threads.push_back(vr.out);
        //vm.vm_run(0);

        //auto result = vm.env.pop();
        std::cout<<node->head->head->head->head->factor->token->content<<std::endl;
    }
    catch (parser_error::UnexpectedTokenError& e) {
        e.printError();
    }
    return 0;
}
