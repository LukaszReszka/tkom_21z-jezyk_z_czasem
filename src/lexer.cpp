#include "lexer.h"

Lexer::Lexer(CodeSource *s) : source(s) {
    single_char_token['+'] = [](Token *token) { token->type = T_PLUS; };
    single_char_token['-'] = [](Token *token) { token->type = T_MINUS; };
    single_char_token['*'] = [](Token *token) { token->type = T_MULTIPLY; };
    single_char_token['/'] = [](Token *token) { token->type = T_DIVIDE; };
    single_char_token['&'] = [](Token *token) { token->type = T_AND; };
    single_char_token['|'] = [](Token *token) { token->type = T_OR; };
    single_char_token['('] = [](Token *token) { token->type = T_PARENTHESES_1; };
    single_char_token[')'] = [](Token *token) { token->type = T_PARENTHESES_2; };
    single_char_token['{'] = [](Token *token) { token->type = T_BRACE_1; };
    single_char_token['}'] = [](Token *token) { token->type = T_BRACE_2; };
    single_char_token[','] = [](Token *token) { token->type = T_COMMA; };
    single_char_token[';'] = [](Token *token) { token->type = T_SEMICOLON; };

    key_words["FUNC"] = [](Token *token) { token->type = T_FUNC; };
    key_words["if"] = [](Token *token) { token->type = T_IF; };
    key_words["else"] = [](Token *token) { token->type = T_ELSE; };
    key_words["while"] = [](Token *token) { token->type = T_WHILE; };
    key_words["RET"] = [](Token *token) { token->type = T_RET; };
}

void Lexer::getNextToken(Token *token) {
    if (!must_read_buf_again) {
        setNextChar();
    } else {
        must_read_buf_again = false;
    }

    skipWhiteCharsAndComment();

    token->column = buf.column;
    token->line = buf.line;

    if (buf.isEndOfText) {
        token->type = T_END;
        return;
    }

    auto func = single_char_token.find(buf.readChar);
    if (func != single_char_token.end()) {
        func->second(token);
        return;
    }

    switch (buf.readChar) {
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

    if (isalpha(buf.readChar)) {
        identifierToken(token);
        return;
    }

    if (isdigit(buf.readChar)) {
        numberToken(token);
        return;
    }

    token->type = T_UNKNOWN;
    token->value = "" + buf.readChar;
}

void Lexer::assignOrComparisonOperatorToken(Token *token) {
    setNextChar();
    char c = buf.readChar;
    if (c == '=') {
        token->type = T_EQUAL;
    } else if (c == '\\') {
        setNextChar();
        if (buf.readChar == '=') {
            token->type = T_NOT_EQUAL;
        } else {
            token->type = T_UNKNOWN;
            token->value = "=\\";
            must_read_buf_again = true;
        }
    } else {
        token->type = T_ASSIGN;
        must_read_buf_again = true;
    }
}

void Lexer::greaterOperatorToken(Token *token) {
    setNextChar();
    if (buf.readChar == '=') {
        token->type = T_GREATER_E;
    } else {
        token->type = T_GREATER;
        must_read_buf_again = true;
    }
}

void Lexer::lesserOperatorToken(Token *token) {
    setNextChar();
    if (buf.readChar == '=') {
        token->type = T_LESSER_E;
    } else {
        token->type = T_LESSER;
        must_read_buf_again = true;
    }
}

void Lexer::unitOrTimeMomentToken(Token *token) {
    setNextChar();
    if (!isdigit(buf.readChar)) {
        unitToken(token);
    } else {

    }
}

void Lexer::unitToken(Token *token) {
    char unit_char = buf.readChar;
    setNextChar();
    if (buf.readChar == ']') {
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
                return;
            }
        }
    } else {
        token->type = T_UNKNOWN;
        token->value = "[" + unit_char;
        must_read_buf_again = true;
    }
}

void Lexer::stringToken(Token *token) {
    std::string res = "";
    setNextChar();
    char c = buf.readChar;
    while (isalnum(c) || c == ' ' || c == '\t' || c == '\\') {
        if (c == '\\') {
            setNextChar();
            if (buf.readChar != '\"') {
                res += '\\';
                token->type = T_UNKNOWN;
                token->value = res;
                must_read_buf_again = true;
                return;
            }
        }
        res += c;
        setNextChar();
        c = buf.readChar;
    }

    if (c == '\"') {
        token->type = T_STRING;
        token->value = res;
    } else {
        token->type = T_UNKNOWN;
        token->value = res;
        must_read_buf_again = true;
    }
}

void Lexer::skipWhiteCharsAndComment() {
    if (buf.isEndOfText) return;

    while (isspace(buf.readChar) || buf.readChar == ' ') {
        setNextChar();
    }

    if (buf.readChar == '#') {
        do {
            setNextChar();
        } while (!buf.isEndOfText && buf.readChar != '#');
        if (buf.readChar == '#')
            setNextChar();
    }

    if (buf.isEndOfText) return;

    if (isspace(buf.readChar) || buf.readChar == ' ' || buf.readChar == '#')
        skipWhiteCharsAndComment();
}

void Lexer::identifierToken(Token *token) {
    std::string res = "";
    res += buf.readChar;
    setNextChar();
    while (isalnum(buf.readChar) || buf.readChar == '_') {
        res += buf.readChar;
        setNextChar();
    }
    must_read_buf_again = true;
    token->type = T_IDENTIFIER;
    token->value = res;
}

void Lexer::numberToken(Token *token) {
    int res = buf.readChar - '0';
    if (res == 0) {
        setNextChar();
        addFractionalPart(token, res);
    } else {
        setNextChar();
        while (isdigit(buf.readChar)) {
            res = 10 * res + (buf.readChar - '0');
            setNextChar();
        }
        addFractionalPart(token, res);
    }
}

void Lexer::addFractionalPart(Token *token, int int_part) {
    int frac = 0;
    if (buf.readChar == '.') {
        setNextChar();
        if (isdigit(buf.readChar)) {
            uint n = 10;
            while (isdigit(buf.readChar)) {
                frac = frac * 10 + (buf.readChar - '0');
                setNextChar();
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
    must_read_buf_again = true;
}