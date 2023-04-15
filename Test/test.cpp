//
// Created by BALL on 2023/4/15.
//

#include "test.h"
#include "../Frontend/parser/parser.h"

void sakTest::testStatementGeneration() {
    try {
        lexer::Lexer lex("let a = 1, b: int = 45;");
        lex.generate();

        parser::Parser p(lex.out);

        auto node = p.generateProgramObject();

        debug(!node->empty(), "1");
    }
    SAK_PARSER_ERROR_CATCH
}
