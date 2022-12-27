#include "Backend/scope/value.h"


int main() {
    lexer::Lexer lex("1+5*4+3-a.b");
    lex.generate();

    parser::Parser p(lex.out);
    auto node = p.parseAddExpressionNode();

    visitor::Visitor vr(node);
    vr.visitAddExpression(node);

    for(auto c: vr.out) {
        std::cout<<visitor::kind_to_string(c.kind)<<" ";
        std::cout<<c.val<<std::endl;
    }
    return 0;
}
