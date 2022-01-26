/* TKOM21Z - Język z czasem
 * Autor: Łukasz Reszka (300257)
 * */

#include "interpreter/interpreter.h"

int main(int argc, char *argv[]) {

    if (argc > 2) {
        std::cerr << "Too many arguments provided\n";
        return -1;
    } else if (argc == 2) {
        std::string flag(argv[1]);
        if (flag != "-t") {
            std::cerr << "Unknown execution flag\n";
            return -1;
        }
    }

    interpreter::Interpreter interpreter(std::cin);

    if (argc == 2)
        interpreter.showProgramTree();

    interpreter.executeProgram();
    std::cout << "\n";
    return 0;
}