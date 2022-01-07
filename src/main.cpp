/* TKOM21Z - Język z czasem
 * Autor: Łukasz Reszka (300257)
 * */

#include <iostream>
#include "codeSource/codeSource.h"
#include "lexer/lexer.h"
#include "parser/parser.h"

int main() {
    code_source::CodeSource source(std::cin);
    lexer::Lexer lexer(source);
    parser::ProgramNode *program = new parser::ProgramNode();
    parser::Parser parser(lexer, program);
    std::cout << program->getTextRepresentation(0);
    return 0;
}
