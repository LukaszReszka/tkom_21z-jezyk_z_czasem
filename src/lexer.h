#ifndef JEZYK_Z_CZASEM_LEXER_H
#define JEZYK_Z_CZASEM_LEXER_H

#include "token.h"
#include "codeSource.h"
#include <map>

class Lexer {

public:
    Lexer(CodeSource *s);

    ~Lexer() { delete source; }

    void getNextToken(Token *token);

private:
    CodeSource *source;
    CharAndPosition buf;
    bool must_read_buf_again = false;
    std::map<char, void (*)(Token *)> single_char_token;   //maps first read char to proper function/lambda
    std::map<std::string, void (*)(Token *)> key_words;

    inline void setNextChar() { buf = source->getNextChar(); }

    void assignOrComparisonOperatorToken(Token *token);

    void greaterOperatorToken(Token *token);

    void lesserOperatorToken(Token *token);

    void unitOrTimeMomentToken(Token *token);

    void unitToken(Token *token);

    void stringToken(Token *token);

    void skipWhiteCharsAndComment();

    void identifierToken(Token *token);

    void numberToken(Token *token);

    void addFractionalPart(Token *token, int int_part);
};


#endif //JEZYK_Z_CZASEM_LEXER_H
