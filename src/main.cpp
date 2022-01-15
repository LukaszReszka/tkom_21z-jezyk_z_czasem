/* TKOM21Z - Język z czasem
 * Autor: Łukasz Reszka (300257)
 * */

#include <iostream>
#include <sstream>
#include "parser/parser.h"

int main() {
//    code_source::CodeSource source(std::cin);
//    lexer::Lexer lexer(source);
//    parser::Parser parser(lexer);
//    std::unique_ptr<parser::ProgramTree> programTree = std::move(parser.parseProgram());
//    std::cout << programTree->toString();

    string code = "a = [m]60 / 2";
    std::stringstream code_to_test(code);
    code_source::CodeSource source(code_to_test);
    lexer::Lexer lexer(source);
    parser::Parser parser(lexer);
    unique_ptr<parser::ProgramTree> tree = std::move(parser.parseProgram());
    std::cout << tree->toString();

    return 0;
}
