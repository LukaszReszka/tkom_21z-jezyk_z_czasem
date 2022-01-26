/* TKOM21Z - Język z czasem
 * Autor: Łukasz Reszka (300257)
 * */

#include <sstream>
#include "interpreter/interpreter.h"

int main() {
//    interpreter::Interpreter interpreter(std::cin);
//    interpreter.showProgramTree();
//    interpreter.executeProgram();

    string code = "a = 2 + 3"
                  "a = a + 1"
                  "SHOW(a)";
    std::stringstream code_to_test(code);
    interpreter::Interpreter interpreter(code_to_test);
    interpreter.showProgramTree();
    std::cout << "\n\n";
    interpreter.executeProgram();
    return 0;
}
