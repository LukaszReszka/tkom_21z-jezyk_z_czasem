#ifndef JEZYK_Z_CZASEM_INTERPRETER_H
#define JEZYK_Z_CZASEM_INTERPRETER_H

#include <memory>
#include <iostream>
#include "../parser/parser.h"
#include "context.h"

namespace interpreter {
    class Interpreter {
    public:

        explicit Interpreter(std::istream &input);

        inline void showProgramTree() {
            if (!hasErrorOccurred)
                std::cout << programTree->toString(0) << "\n\n------------------------------\n\n";
        }

        void executeProgram();

    private:
        bool hasErrorOccurred = false, hasExecutionFinished = false;
        std::unique_ptr<parser::ProgramTree> programTree;
        std::shared_ptr<Context> execute_context;
    };
}

#endif //JEZYK_Z_CZASEM_INTERPRETER_H
