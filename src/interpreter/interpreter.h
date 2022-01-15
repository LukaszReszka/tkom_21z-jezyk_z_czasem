#ifndef JEZYK_Z_CZASEM_INTERPRETER_H
#define JEZYK_Z_CZASEM_INTERPRETER_H

#include <memory>
#include <iostream>
#include "../parser/parser.h"

namespace interpreter {
    class Interpreter {
    public:

        explicit Interpreter(std::istream &input);

        inline void showProgramTree() { std::cout << programTree->toString(); }

        void execudeProgram();

    private:
        std::unique_ptr<parser::ProgramTree> programTree;
    };
}

#endif //JEZYK_Z_CZASEM_INTERPRETER_H
