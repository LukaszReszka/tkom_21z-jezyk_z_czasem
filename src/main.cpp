/* TKOM21Z - Język z czasem
 * Autor: Łukasz Reszka (300257)
 * */

#include "interpreter/interpreter.h"

int main() {
    interpreter::Interpreter interpreter(std::cin);
//    interpreter.showProgramTree();
    interpreter.executeProgram();
    return 0;
}
