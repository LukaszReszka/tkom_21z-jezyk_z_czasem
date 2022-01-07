#include "codeSource.h"

namespace code_source {
    CharAndPosition CodeSource::getNextChar() {
        char c;
        source.get(c);

        if (source.eof()) {
            CharAndPosition eofChar(line + 1, column + 1);
            return eofChar;
        }

        CharAndPosition readChar(c, line + 1, column + 1);
        ++column;
        if (c == '\n') {
            ++line;
            column = 0;
        }

        return readChar;
    }

    CharAndPosition CodeSource::peekNextChar() {
        char c = source.peek();

        if (source.eof()) {
            CharAndPosition eofChar(line + 1, column + 1);
            return eofChar;
        } else {
            CharAndPosition readChar(c, line + 1, column + 1);
            return readChar;
        }
    }
}