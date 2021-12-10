#ifndef JEZYK_Z_CZASEM_LEXER_H
#define JEZYK_Z_CZASEM_LEXER_H

#include "token.h"
#include "../codeSource/codeSource.h"
#include <map>

namespace lexer {

    class Lexer {

    public:
        Lexer(code_source::CodeSource s);

        Token getNextToken();

    private:
        code_source::CodeSource source;
        code_source::CharAndPosition current_char;
        std::map<char, token_type> single_char_token;
        std::map<std::string, token_type> key_words;

        bool isMultipleCharToken(Token *token);

        void assignOrComparisonOperatorToken(Token *token);

        void greaterLessOrEqualOperatorToken(Token *token, token_type cannot_be_equal, token_type can_be_equal);

        void unitOrTimeToken(Token *token);

        void unitToken(Token *token);

        void stringToken(Token *token);

        void skipWhiteCharsAndComment();

        void identifierToken(Token *token);

        void numberToken(Token *token);

        void addFractionalPart(Token *token, int int_part);

        void getTimePeriodToken(Token *token);

        void getTimeMomentToken(Token *token);

        void getClockToken(Token *token);

        bool getTime(bool isMax24h, TimeMoment *moment, TimePeriod *period);

        bool getDate(TimeMoment *moment);

        int getHour(bool isMax24h);

        int getMinSecDayOrMonth(int upper_limit, bool isZeroAllowed = true);

        int getYear();
    };
}

#endif //JEZYK_Z_CZASEM_LEXER_H
