#ifndef JEZYK_Z_CZASEM_CHARANDPOSITION_H
#define JEZYK_Z_CZASEM_CHARANDPOSITION_H

#include "position.h"

namespace code_source {

    typedef unsigned int uint;

    struct CharAndPosition {
        char value;
        bool isEndOfText;
        Position position;

        CharAndPosition() {}

        CharAndPosition(char c, uint lin, uint col) : value(c), isEndOfText(false),
                                                      position(lin, col) {}

        CharAndPosition(uint lin, uint col) : value('$'), isEndOfText(true),
                                              position(lin, col) {}
    };
}

#endif //JEZYK_Z_CZASEM_CHARANDPOSITION_H
