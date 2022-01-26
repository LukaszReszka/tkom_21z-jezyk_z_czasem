/* TKOM21Z - Język z czasem
 * Autor: Łukasz Reszka (300257)
 * */

#include <sstream>
#include "interpreter/interpreter.h"

int main() {
//    interpreter::Interpreter interpreter(std::cin);
//    interpreter.showProgramTree();
//    interpreter.execudeProgram();

    string code = ".func(\"ala\")";
    std::stringstream code_to_test(code);
    interpreter::Interpreter interpreter(code_to_test);
    interpreter.showProgramTree();
    std::cout << "\n\n\n";
    //interpreter.execudeProgram();
    return 0;
}
