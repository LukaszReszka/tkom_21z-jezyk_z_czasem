#ifndef JEZYK_Z_CZASEM_CHARANDPOSITION_H
#define JEZYK_Z_CZASEM_CHARANDPOSITION_H

typedef unsigned int uint;

struct CharAndPosition {
    char readChar;
    bool isEndOfText;
    uint column;
    uint line;

    CharAndPosition() {}

    CharAndPosition(char c, uint lin, uint col) : readChar(c), isEndOfText(false),
                                                  column(col), line(lin) {}

    CharAndPosition(uint lin, uint col) : readChar('$'), isEndOfText(true),
                                          column(col), line(lin) {}
};

#endif //JEZYK_Z_CZASEM_CHARANDPOSITION_H
