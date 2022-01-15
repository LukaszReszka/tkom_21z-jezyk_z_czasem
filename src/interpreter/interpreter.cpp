#include <iostream>
#include "interpreter.h"

namespace interpreter {

    Interpreter::Interpreter(std::istream &input) {
        try {
            code_source::CodeSource source(input);
            lexer::Lexer lexer(source);
            parser::Parser parser(lexer);
            programTree = std::move(parser.parseProgram());
        } catch (std::runtime_error &e) {
            std::cout << "Wyjątek!!!\n";
            //TODO wyświetlenie komunikatu błędu gramatycznego lub leksykalnego
        }
    }
}