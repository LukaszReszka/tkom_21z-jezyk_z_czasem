/* TKOM21Z - Język z czasem
 * Autor: Łukasz Reszka (300257)
 * */

#include <iostream>
#include "codeSource.h"

int main(int argc, char **argv) {
    CodeSource *source;

    if (argc == 2) {            //source code from file

        std::string launch_arg = std::string(argv[1]);

        if (launch_arg.size() < 5 || launch_arg.substr(launch_arg.size() - 4, 4) != ".txt") {
            std::cerr << "\033[31mInvalid argument - input name of TXT file with source code (for example: code.txt)"
                      << std::endl;
            return -1;
        }
        try {
            source = new CodeSource(launch_arg);
        } catch (...) {
            std::cerr << "\033[31mError - file not found!" << std::endl;
            return -1;
        }

    } else if (argc == 1) {     //source code from console
        source = new CodeSource(std::cin);
    } else {
        std::cerr << "\033[31mToo many arguments - at the most one argument allowed!" << std::endl;
        return -1;
    }
    
    delete source;
    return 0;
}
