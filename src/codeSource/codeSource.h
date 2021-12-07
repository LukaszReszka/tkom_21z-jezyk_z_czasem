#ifndef JEZYK_Z_CZASEM_CODESOURCE_H
#define JEZYK_Z_CZASEM_CODESOURCE_H

#include <fstream>
#include <vector>
#include "charAndPosition.h"

namespace code_source {

    const std::string FINISH_TYPING_SYMBOL = "^q";

    class CodeSource {

    public:
        explicit CodeSource(std::istream &input);

        explicit CodeSource(std::string &file_name);

        ~CodeSource();

        CharAndPosition getNextChar() { return (this->*getCharFunc)(); }

    private:
        uint line = 0;

        uint column = 0;

        std::fstream source_file;

        std::vector<std::string> commands;

        CharAndPosition (CodeSource::*getCharFunc)();   //pointer to chosen function

        CharAndPosition getCharFromFile();

        CharAndPosition getCharFromTerminal();
    };
}

#endif //JEZYK_Z_CZASEM_CODESOURCE_H
