#include <iostream>
#include "interpreter.h"

namespace interpreter {

    Interpreter::Interpreter(std::istream &input) {
        execute_context = std::make_shared<Context>();
        if (!hasErrorOccurred) {
            try {
                code_source::CodeSource source(input);
                lexer::Lexer lexer(source);
                parser::Parser parser(lexer, execute_context);
                programTree = std::move(parser.parseProgram());
            } catch (std::runtime_error &e) {
                hasErrorOccurred = true;
                std::cout << "Wyjątek!!!\n";
                //TODO wyświetlenie komunikatu błędu gramatycznego lub leksykalnego
            }
        }
    }

    void Interpreter::execudeProgram() {
        if (!hasErrorOccurred && !hasExecutionFinished) {
            try {
                programTree->execute();
                hasExecutionFinished = true;
            } catch (std::runtime_error &e) {
                hasErrorOccurred = true;
                std::cout << "Wyjątek semantyczny!!!\n";
                //TODO wyświetlenie komunikatu błędu semantycznego
            }
        }
    }
}