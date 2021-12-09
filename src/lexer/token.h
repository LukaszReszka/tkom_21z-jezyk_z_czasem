#ifndef JEZYK_Z_CZASEM_TOKEN_H
#define JEZYK_Z_CZASEM_TOKEN_H

#include <variant>
#include <string>
#include "timeMoment.h"
#include "timePeriod.h"
#include "../codeSource/position.h"

namespace lexer {

    enum token_type {       // all white chars and comments # ... # are skipped
        T_FUNC,             //keywords
        T_IF,
        T_ELSE,
        T_WHILE,
        T_RET,
        T_IDENTIFIER,       //name of variable or function
        T_STRING,           //"He said \"No\""
        T_INT,
        T_DOUBLE,
        T_SEC_U,            //[s]
        T_MIN_U,            //[m]
        T_HOUR_U,           //[h]
        T_DAY_U,            //[d]
        T_DATE,             //[21/03/2021]
        T_TIMESTAMP,        //[21/03/2021 18:54:32]
        T_CLOCK,            //[18:54:32]
        T_TIME_PERIOD,      //[+2:15:01]
        T_ASSIGN,           // =
        T_PLUS,             // +
        T_MINUS,            // -
        T_MULTIPLY,         // *
        T_DIVIDE,           // /
        T_OR,               // |
        T_AND,              // &
        T_EQUAL,            // ==
        T_NOT_EQUAL,        // =\=
        T_GREATER,          // >
        T_GREATER_E,        // >=
        T_LESS,           // <
        T_LESS_E,         // <=
        T_SEMICOLON,
        T_COMMA,
        T_PARENTHESES_1,    // (
        T_PARENTHESES_2,    // )
        T_BRACE_1,          // {
        T_BRACE_2,          // }
        T_END,              //EOF or ^q
        T_NUMBER_TOO_LARGE,
        T_UNKNOWN
    };

    struct Token {
        code_source::Position position;
        token_type type;
        std::variant<int, double, std::string, TimeMoment, TimePeriod> value;
    };

}

#endif //JEZYK_Z_CZASEM_TOKEN_H
