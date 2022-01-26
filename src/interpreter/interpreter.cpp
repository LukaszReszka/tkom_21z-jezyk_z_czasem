#include "interpreter.h"
#include "../parser/tln_exception.h"

namespace interpreter {

    Interpreter::Interpreter(std::istream &input) {
        execute_context = std::make_shared<Context>();
        if (!hasErrorOccurred) {
            try {
                code_source::CodeSource source(input);
                lexer::Lexer lexer(source);
                parser::Parser parser(lexer, execute_context);
                programTree = std::move(parser.parseProgram());
            } catch (tln_exception &e) {
                hasErrorOccurred = true;
                std::cerr << e.what();
            }
        }
    }

    void Interpreter::executeProgram() {
        if (!hasErrorOccurred && !hasExecutionFinished) {
            try {
                programTree->execute();
                hasExecutionFinished = true;
            } catch (tln_exception &e) {
                hasErrorOccurred = true;
                std::cerr << e.what();
            }
        }
    }
}