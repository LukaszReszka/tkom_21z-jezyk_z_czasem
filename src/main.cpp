/* TKOM21Z - Język z czasem
 * Autor: Łukasz Reszka (300257)
 * */

#include "interpreter/interpreter.h"
#include <sstream>

int main() {
    std::stringstream code("a = 1,"
                           "a = 1 + a,"
                           "SHOW(a)");
    interpreter::Interpreter interpreter(/*std::cin*/code);
    interpreter.showProgramTree();
    interpreter.executeProgram();
    return 0;
}