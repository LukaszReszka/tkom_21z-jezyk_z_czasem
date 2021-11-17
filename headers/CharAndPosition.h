/* TKOM21Z - Język z czasem
 * Autor: Łukasz Reszka (300257)
 * */

#ifndef JEZYK_Z_CZASEM_CHARANDPOSITION_H
#define JEZYK_Z_CZASEM_CHARANDPOSITION_H

typedef unsigned int uint;

struct CharAndPosition {
    char readChar;
    bool endOfText;
    uint column;
    uint line;

    CharAndPosition(char c, uint lin, uint col) : readChar(c), endOfText(false),
                                                  column(col), line(lin) {}

    CharAndPosition(uint lin, uint col) : endOfText(true), column(col), line(lin) {}
};

#endif //JEZYK_Z_CZASEM_CHARANDPOSITION_H
