/* TKOM21Z - Język z czasem
 * Autor: Łukasz Reszka (300257)
 * */

#include <sstream>
#include "interpreter/interpreter.h"

int main() {
//    interpreter::Interpreter interpreter(std::cin);
//    interpreter.showProgramTree();

    string code = "a = 4";
    std::stringstream code_to_test(code);
    interpreter::Interpreter interpreter(code_to_test);
    interpreter.showProgramTree();
    return 0;
}
