/* TKOM21Z - Język z czasem
 * Autor: Łukasz Reszka (300257)
 * */

#include <iostream>
#include <memory>
#include "codeSource/codeSource.h"
#include "lexer/lexer.h"
#include "parser/parser.h"

int main() {
    code_source::CodeSource source(std::cin);
    lexer::Lexer lexer(source);
    parser::Parser parser(lexer);
    std::unique_ptr<parser::ProgramTree> programTree = std::move(parser.parseProgram());
    std::cout << programTree->toString();
    return 0;
}
