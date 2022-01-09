#ifndef JEZYK_Z_CZASEM_CODESOURCE_H
#define JEZYK_Z_CZASEM_CODESOURCE_H

#include <istream>
#include "charAndPosition.h"

namespace code_source {

    class CodeSource {

    public:
        explicit CodeSource(std::istream &input) : source(input) {}

        CharAndPosition getNextChar();

        CharAndPosition peekNextChar();

        void skipChar();

    private:
        uint line = 0;
        uint column = 0;

        std::istream &source;
    };
}

#endif //JEZYK_Z_CZASEM_CODESOURCE_H
