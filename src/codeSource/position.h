#ifndef JEZYK_Z_CZASEM_POSITION_H
#define JEZYK_Z_CZASEM_POSITION_H

typedef unsigned int uint;

namespace code_source {

    struct Position {
        uint column;
        uint line;

        Position() {}

        Position(uint lin, uint col) : column(col), line(lin) {}
    };

}

#endif //JEZYK_Z_CZASEM_POSITION_H
