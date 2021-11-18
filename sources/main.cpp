/* TKOM21Z - Język z czasem
 * Autor: Łukasz Reszka (300257)
 * */

#include <iostream>
#include "../headers/CodeSource.h"

int main(int argc, char **argv) {
    CodeSource *source;

    if (argc == 2) {            //source code from file

        std::string launch_arg = std::string(argv[1]);

        if (launch_arg.size() < 5 || launch_arg.substr(launch_arg.size() - 4, 4) != ".txt") {
            std::cerr << "Invalid argument - input name of TXT file with source code (for example: code.txt)"
                      << std::endl;
            return -1;
        }
        try {
            source = new CodeSource(launch_arg);
        } catch (...) {
            std::cerr << "Error - file not found!" << std::endl;
            return -1;
        }

    } else if (argc == 1) {     //source code from console
        source = new CodeSource();
    } else {
        std::cerr << "Too many arguments - at the most one argument allowed!" << std::endl;
        return -1;
    }

    delete source;
    return 0;
}
