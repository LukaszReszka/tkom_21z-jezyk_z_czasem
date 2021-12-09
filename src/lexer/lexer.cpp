#include "lexer.h"

namespace lexer {

    Lexer::Lexer(code_source::CodeSource s) : source(s) {
        single_char_token['+'] = T_PLUS;
        single_char_token['-'] = T_MINUS;
        single_char_token['*'] = T_MULTIPLY;
        single_char_token['/'] = T_DIVIDE;
        single_char_token['&'] = T_AND;
        single_char_token['|'] = T_OR;
        single_char_token['('] = T_PARENTHESES_1;
        single_char_token[')'] = T_PARENTHESES_2;
        single_char_token['{'] = T_BRACE_1;
        single_char_token['}'] = T_BRACE_2;
        single_char_token[','] = T_COMMA;
        single_char_token[';'] = T_SEMICOLON;

        key_words["FUNC"] = T_FUNC;
        key_words["if"] = T_IF;
        key_words["else"] = T_ELSE;
        key_words["while"] = T_WHILE;
        key_words["RET"] = T_RET;
    }

    void Lexer::getNextToken(Token *token) {
        current_char = source.getNextChar();

        skipWhiteCharsAndComment();

        token->position = current_char.position;

        if (current_char.isEndOfText) {
            token->type = T_END;
            return;
        }

        auto func = single_char_token.find(current_char.value);
        if (func != single_char_token.end()) {
            token->type = func->second;
            return;
        }

        switch (current_char.value) {
            case '=':
                assignOrComparisonOperatorToken(token);
                return;

            case '>':
                greaterOperatorToken(token);
                return;

            case '<':
                lesserOperatorToken(token);
                return;

            case '[':
                unitOrTimeMomentToken(token);
                return;

            case '"':
                stringToken(token);
                return;
        }

        if (isalpha(current_char.value)) {
            identifierToken(token);
            return;
        }

        if (isdigit(current_char.value)) {
            numberToken(token);
            return;
        }

        token->type = T_UNKNOWN;
        token->value = "" + current_char.value;
    }

    void Lexer::assignOrComparisonOperatorToken(Token *token) {
        current_char = source.peekNextChar();
        if (current_char.value == '=') {
            token->type = T_EQUAL;
            source.skipChar();
        } else if (current_char.value == '\\') {
            source.skipChar();
            current_char = source.peekNextChar();
            if (current_char.value == '=') {
                token->type = T_NOT_EQUAL;
                source.skipChar();
            } else {
                token->type = T_UNKNOWN;
                token->value = "=\\";
            }
        } else {
            token->type = T_ASSIGN;
        }
    }

    void Lexer::greaterOperatorToken(Token *token) {
        current_char = source.peekNextChar();
        if (current_char.value == '=') {
            token->type = T_GREATER_E;
            source.skipChar();
        } else {
            token->type = T_GREATER;
        }
    }

    void Lexer::lesserOperatorToken(Token *token) {
        current_char = source.peekNextChar();
        if (current_char.value == '=') {
            token->type = T_LESSER_E;
            source.skipChar();
        } else {
            token->type = T_LESSER;
        }
    }

    void Lexer::unitOrTimeMomentToken(Token *token) {
        current_char = source.peekNextChar();
        if (!isdigit(current_char.value)) {
            source.skipChar();
            unitToken(token);
        } else {
            //body - tokeny datowe ...
        }
    }

    void Lexer::unitToken(Token *token) {
        char unit_char = current_char.value;
        current_char = source.peekNextChar();
        if (current_char.value == ']') {
            switch (unit_char) {
                case 's':
                    token->type = T_SEC_U;
                    break;

                case 'm':
                    token->type = T_MIN_U;
                    break;

                case 'h':
                    token->type = T_HOUR_U;
                    break;

                case 'd':
                    token->type = T_DAY_U;
                    break;

                default: {
                    token->type = T_UNKNOWN;
                    std::string res = "[" + unit_char;
                    token->value = res + "]";
                }
            }
            source.skipChar();
        } else {
            token->type = T_UNKNOWN;
            token->value = "[" + unit_char;
        }
    }

    void Lexer::stringToken(Token *token) {
        std::string res = "";
        current_char = source.peekNextChar();
        char c = current_char.value;
        while (isalnum(c) || c == ' ' || c == '\t' || c == '\\') {
            if (c == '\\') {
                source.skipChar();
                current_char = source.peekNextChar();
                if (current_char.value != '\"') {
                    res += '\\';
                    token->type = T_UNKNOWN;
                    token->value = res;
                    return;
                }
            }
            res += c;
            source.skipChar();
            current_char = source.peekNextChar();
            c = current_char.value;
        }

        if (c == '\"') {
            token->type = T_STRING;
            token->value = res;
            source.skipChar();
        } else {
            token->type = T_UNKNOWN;
            token->value = res;
        }
    }

    void Lexer::skipWhiteCharsAndComment() {
        if (current_char.isEndOfText) return;

        while (isspace(current_char.value) || current_char.value == ' ') {
            current_char = source.getNextChar();
        }

        if (current_char.value == '#') {
            do {
                current_char = source.getNextChar();
            } while (!current_char.isEndOfText && current_char.value != '#');
            if (current_char.value == '#')
                current_char = source.peekNextChar();
        }

        if (isspace(current_char.value) || current_char.value == ' ' || current_char.value == '#') {
            if (current_char.value == '#')
                source.skipChar();
            skipWhiteCharsAndComment();
        }
    }

    void Lexer::identifierToken(Token *token) {
        std::string res = "";
        res += current_char.value;
        current_char = source.peekNextChar();
        while (isalnum(current_char.value) || current_char.value == '_') {
            source.skipChar();
            res += current_char.value;
            current_char = source.peekNextChar();
        }
        token->type = T_IDENTIFIER;
        token->value = res;
    }

    void Lexer::numberToken(Token *token) {
        int res = current_char.value - '0';
        if (res == 0) {
            current_char = source.peekNextChar();
            addFractionalPart(token, res);
        } else {
            current_char = source.peekNextChar();
            while (isdigit(current_char.value)) {
                source.skipChar();
                res = 10 * res + (current_char.value - '0');
                current_char = source.peekNextChar();
            }
            addFractionalPart(token, res);
        }
    }

    void Lexer::addFractionalPart(Token *token, int int_part) {
        int frac = 0;
        if (current_char.value == '.') {
            source.skipChar();
            current_char = source.peekNextChar();
            if (isdigit(current_char.value)) {
                uint n = 10;
                while (isdigit(current_char.value)) {
                    frac = frac * 10 + (current_char.value - '0');
                    source.skipChar();
                    current_char = source.peekNextChar();
                    n *= 10;
                }
                double result = int_part + (frac / n);
                token->type = T_DOUBLE;
                token->value = result;
            } else {
                token->type = T_INT;
                token->value = 0;
            }
        } else {
            token->type = T_INT;
            token->value = 0;
        }
    }
}