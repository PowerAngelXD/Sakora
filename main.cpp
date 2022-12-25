#include "Fronted/parser/parser.h"

int main() {
    lexer::Lexer lex("1+3*4");
    lex.generate();

    parser::Parser p(lex.out);
    auto node = p.parseAddExpressionNode();

    std::cout<<node.kind<<std::endl;
    return 0;
}
