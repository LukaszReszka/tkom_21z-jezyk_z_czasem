#include <sstream>
#include <vector>
#include "../libs/doctest/include/doctest.h"
#include "../src/lexer/lexer.h"

using std::vector, std::string, std::stringstream, std::holds_alternative;
using lexer::Token, lexer::token_type;

TEST_SUITE_BEGIN("Lexer tests - tokens recognition");

stringstream input_chars;
vector<Token> recognised_tokens;

void recogniseAllTokens() {
    recognised_tokens.clear();
    code_source::CodeSource source(input_chars);
    lexer::Lexer lex(source);
    bool eofFound = false;
    Token current_token;
    while (!eofFound) {
        current_token = lex.getNextToken();
        eofFound = (current_token.type == lexer::T_END);
        recognised_tokens.push_back(current_token);
    }
}

TEST_CASE("Keywords and identifiers recognition") {
    input_chars.clear();

    SUBCASE("FUNC") {
        input_chars << "FUNC";
        REQUIRE_NOTHROW(recogniseAllTokens());
        REQUIRE_EQ(2, recognised_tokens.size());

        CHECK_EQ(token_type::T_FUNC, recognised_tokens[0].type);
        CHECK_EQ(1, recognised_tokens[0].position.line);
        CHECK_EQ(1, recognised_tokens[0].position.column);

        CHECK_EQ(token_type::T_END, recognised_tokens[1].type);
        CHECK_EQ(1, recognised_tokens[1].position.line);
        CHECK_EQ(5, recognised_tokens[1].position.column);
    }

    SUBCASE("if") {
        input_chars << "if";
        REQUIRE_NOTHROW(recogniseAllTokens());
        REQUIRE_EQ(2, recognised_tokens.size());

        CHECK_EQ(token_type::T_IF, recognised_tokens[0].type);
        CHECK_EQ(1, recognised_tokens[0].position.line);
        CHECK_EQ(1, recognised_tokens[0].position.column);

        CHECK_EQ(token_type::T_END, recognised_tokens[1].type);
        CHECK_EQ(1, recognised_tokens[1].position.line);
        CHECK_EQ(3, recognised_tokens[1].position.column);
    }

    SUBCASE("elif") {
        input_chars << "elif";
        REQUIRE_NOTHROW(recogniseAllTokens());
        REQUIRE_EQ(2, recognised_tokens.size());

        CHECK_EQ(token_type::T_ELIF, recognised_tokens[0].type);
        CHECK_EQ(1, recognised_tokens[0].position.line);
        CHECK_EQ(1, recognised_tokens[0].position.column);

        CHECK_EQ(token_type::T_END, recognised_tokens[1].type);
        CHECK_EQ(1, recognised_tokens[1].position.line);
        CHECK_EQ(5, recognised_tokens[1].position.column);
    }

    SUBCASE("else") {
        input_chars << "else";
        REQUIRE_NOTHROW(recogniseAllTokens());
        REQUIRE_EQ(2, recognised_tokens.size());

        CHECK_EQ(token_type::T_ELSE, recognised_tokens[0].type);
        CHECK_EQ(1, recognised_tokens[0].position.line);
        CHECK_EQ(1, recognised_tokens[0].position.column);

        CHECK_EQ(token_type::T_END, recognised_tokens[1].type);
        CHECK_EQ(1, recognised_tokens[1].position.line);
        CHECK_EQ(5, recognised_tokens[1].position.column);
    }

    SUBCASE("while") {
        input_chars << "while";
        REQUIRE_NOTHROW(recogniseAllTokens());
        REQUIRE_EQ(2, recognised_tokens.size());

        CHECK_EQ(token_type::T_WHILE, recognised_tokens[0].type);
        CHECK_EQ(1, recognised_tokens[0].position.line);
        CHECK_EQ(1, recognised_tokens[0].position.column);

        CHECK_EQ(token_type::T_END, recognised_tokens[1].type);
        CHECK_EQ(1, recognised_tokens[1].position.line);
        CHECK_EQ(6, recognised_tokens[1].position.column);
    }

    SUBCASE("RET") {
        input_chars << "RET";
        REQUIRE_NOTHROW(recogniseAllTokens());
        REQUIRE_EQ(2, recognised_tokens.size());

        CHECK_EQ(token_type::T_RET, recognised_tokens[0].type);
        CHECK_EQ(1, recognised_tokens[0].position.line);
        CHECK_EQ(1, recognised_tokens[0].position.column);

        CHECK_EQ(token_type::T_END, recognised_tokens[1].type);
        CHECK_EQ(1, recognised_tokens[1].position.line);
        CHECK_EQ(4, recognised_tokens[1].position.column);
    }

    SUBCASE("SHOW") {
        input_chars << "SHOW";
        REQUIRE_NOTHROW(recogniseAllTokens());
        REQUIRE_EQ(2, recognised_tokens.size());

        CHECK_EQ(token_type::T_SHOW, recognised_tokens[0].type);
        CHECK_EQ(1, recognised_tokens[0].position.line);
        CHECK_EQ(1, recognised_tokens[0].position.column);

        CHECK_EQ(token_type::T_END, recognised_tokens[1].type);
        CHECK_EQ(1, recognised_tokens[1].position.line);
        CHECK_EQ(5, recognised_tokens[1].position.column);
    }

    SUBCASE("Identifiers") {
        input_chars << "a b1 c_4\nABC PI_NUMB D1\nsHOW IF\n4F _numb n@me discount%\n";
        REQUIRE_NOTHROW(recogniseAllTokens());
        REQUIRE_EQ(18, recognised_tokens.size());

        string tokens_list[16] = {"a", "b1", "c_4", "ABC", "PI_NUMB", "D1", "sHOW",
                                  "IF", "4", "F", "_", "numb", "n", "@", "me", "discount"};

        unsigned int line = 1, col = 1;

        for (int i = 0; i < 16; ++i) {
            if (i == 8) {           //digit '4' from "4F"
                ++line;
                CHECK_EQ(token_type::T_INT, recognised_tokens[i].type);
                CHECK_EQ(line, recognised_tokens[i].position.line);
                CHECK_EQ(1, recognised_tokens[i].position.column);
                REQUIRE_UNARY(holds_alternative<int>(recognised_tokens[i].value));
                CHECK_EQ(4, std::get<int>(recognised_tokens[i].value));
                col = 2;
            } else {
                if (i == 3 || i == 6) {
                    ++line;
                    col = 1;
                }
                if (i == 10 || i == 13)
                    CHECK_EQ(token_type::T_UNKNOWN, recognised_tokens[i].type);
                else
                    CHECK_EQ(token_type::T_IDENTIFIER, recognised_tokens[i].type);
                CHECK_EQ(line, recognised_tokens[i].position.line);
                CHECK_EQ(col, recognised_tokens[i].position.column);
                REQUIRE_UNARY(holds_alternative<string>(recognised_tokens[i].value));
                CHECK_EQ(tokens_list[i], std::get<string>(recognised_tokens[i].value));

                col += tokens_list[i].size();
                if (i != 10 && i != 12 && i != 13)
                    ++col;
            }
        }

        CHECK_EQ(token_type::T_UNKNOWN, recognised_tokens[16].type);
        CHECK_EQ(4, recognised_tokens[16].position.line);
        CHECK_EQ(23, recognised_tokens[16].position.column);
        REQUIRE_UNARY(holds_alternative<string>(recognised_tokens[16].value));
        CHECK_EQ("%", std::get<string>(recognised_tokens[16].value));

        CHECK_EQ(token_type::T_END, recognised_tokens[17].type);
        CHECK_EQ(5, recognised_tokens[17].position.line);
        CHECK_EQ(1, recognised_tokens[17].position.column);
    }
}

TEST_CASE("String recognition") {
    input_chars.clear();

    SUBCASE("Proper string") {
        string sentence = "She\t walked into the room 97";
        input_chars << "\"" + sentence + "\"";
        REQUIRE_NOTHROW(recogniseAllTokens());
        REQUIRE_EQ(2, recognised_tokens.size());

        CHECK_EQ(token_type::T_STRING, recognised_tokens[0].type);
        CHECK_EQ(1, recognised_tokens[0].position.line);
        CHECK_EQ(1, recognised_tokens[0].position.column);
        REQUIRE_UNARY(holds_alternative<string>(recognised_tokens[0].value));
        CHECK_EQ(sentence, std::get<string>(recognised_tokens[0].value));

        CHECK_EQ(token_type::T_END, recognised_tokens[1].type);
        CHECK_EQ(1, recognised_tokens[1].position.line);
        CHECK_EQ(31, recognised_tokens[1].position.column);
    }

    SUBCASE("String with escaped \"") {
        input_chars << R"("He said \"No\"")";
        REQUIRE_NOTHROW(recogniseAllTokens());
        REQUIRE_EQ(2, recognised_tokens.size());

        CHECK_EQ(token_type::T_STRING, recognised_tokens[0].type);
        CHECK_EQ(1, recognised_tokens[0].position.line);
        CHECK_EQ(1, recognised_tokens[0].position.column);
        REQUIRE_UNARY(holds_alternative<string>(recognised_tokens[0].value));
        CHECK_EQ("He said \"No\"", std::get<string>(recognised_tokens[0].value));

        CHECK_EQ(token_type::T_END, recognised_tokens[1].type);
        CHECK_EQ(1, recognised_tokens[1].position.line);
        CHECK_EQ(17, recognised_tokens[1].position.column);
    }

    SUBCASE("Not-string with inappropriate char") {
        input_chars << "\"We went\nthere\"";
        REQUIRE_NOTHROW(recogniseAllTokens());
        REQUIRE_EQ(4, recognised_tokens.size());

        CHECK_EQ(token_type::T_UNKNOWN, recognised_tokens[0].type);
        CHECK_EQ(1, recognised_tokens[0].position.line);
        CHECK_EQ(1, recognised_tokens[0].position.column);
        REQUIRE_UNARY(holds_alternative<string>(recognised_tokens[0].value));
        CHECK_EQ("We went", std::get<string>(recognised_tokens[0].value));

        CHECK_EQ(token_type::T_IDENTIFIER, recognised_tokens[1].type);
        CHECK_EQ(2, recognised_tokens[1].position.line);
        CHECK_EQ(1, recognised_tokens[1].position.column);
        REQUIRE_UNARY(holds_alternative<string>(recognised_tokens[1].value));
        CHECK_EQ("there", std::get<string>(recognised_tokens[1].value));

        CHECK_EQ(token_type::T_UNKNOWN, recognised_tokens[2].type);
        CHECK_EQ(2, recognised_tokens[2].position.line);
        CHECK_EQ(6, recognised_tokens[2].position.column);
        REQUIRE_UNARY(holds_alternative<string>(recognised_tokens[2].value));
        CHECK_EQ("\"", std::get<string>(recognised_tokens[2].value));

        CHECK_EQ(token_type::T_END, recognised_tokens[3].type);
        CHECK_EQ(2, recognised_tokens[3].position.line);
        CHECK_EQ(7, recognised_tokens[3].position.column);
    }

    SUBCASE("Not-string with last \" escaped") {
        input_chars << R"("We went there\")";
        REQUIRE_NOTHROW(recogniseAllTokens());
        REQUIRE_EQ(2, recognised_tokens.size());

        CHECK_EQ(token_type::T_UNKNOWN, recognised_tokens[0].type);
        CHECK_EQ(1, recognised_tokens[0].position.line);
        CHECK_EQ(1, recognised_tokens[0].position.column);
        REQUIRE_UNARY(holds_alternative<string>(recognised_tokens[0].value));
        CHECK_EQ("We went there\"", std::get<string>(recognised_tokens[0].value));

        CHECK_EQ(token_type::T_END, recognised_tokens[1].type);
        CHECK_EQ(1, recognised_tokens[1].position.line);
        CHECK_EQ(17, recognised_tokens[1].position.column);
    }
}

TEST_CASE("Numbers recognition") {
    input_chars.clear();

    SUBCASE("Correct numbers") {
        input_chars << "1 2. 0\n0.1 3.14\n-5\n-0.07\n";
        REQUIRE_NOTHROW(recogniseAllTokens());
        REQUIRE_EQ(10, recognised_tokens.size());

        CHECK_EQ(token_type::T_INT, recognised_tokens[0].type);
        CHECK_EQ(1, recognised_tokens[0].position.line);
        CHECK_EQ(1, recognised_tokens[0].position.column);
        REQUIRE_UNARY(holds_alternative<int>(recognised_tokens[0].value));
        CHECK_EQ(1, std::get<int>(recognised_tokens[0].value));

        CHECK_EQ(token_type::T_INT, recognised_tokens[1].type);
        CHECK_EQ(1, recognised_tokens[1].position.line);
        CHECK_EQ(3, recognised_tokens[1].position.column);
        REQUIRE_UNARY(holds_alternative<int>(recognised_tokens[1].value));
        CHECK_EQ(2, std::get<int>(recognised_tokens[1].value));

        CHECK_EQ(token_type::T_INT, recognised_tokens[2].type);
        CHECK_EQ(1, recognised_tokens[2].position.line);
        CHECK_EQ(6, recognised_tokens[2].position.column);
        REQUIRE_UNARY(holds_alternative<int>(recognised_tokens[2].value));
        CHECK_EQ(0, std::get<int>(recognised_tokens[2].value));

        CHECK_EQ(token_type::T_DOUBLE, recognised_tokens[3].type);
        CHECK_EQ(2, recognised_tokens[3].position.line);
        CHECK_EQ(1, recognised_tokens[3].position.column);
        REQUIRE_UNARY(holds_alternative<double>(recognised_tokens[3].value));
        CHECK_EQ(0.1, std::get<double>(recognised_tokens[3].value));

        CHECK_EQ(token_type::T_DOUBLE, recognised_tokens[4].type);
        CHECK_EQ(2, recognised_tokens[4].position.line);
        CHECK_EQ(5, recognised_tokens[4].position.column);
        REQUIRE_UNARY(holds_alternative<double>(recognised_tokens[4].value));
        CHECK_EQ(3.14, std::get<double>(recognised_tokens[4].value));

        CHECK_EQ(token_type::T_MINUS, recognised_tokens[5].type);
        CHECK_EQ(3, recognised_tokens[5].position.line);
        CHECK_EQ(1, recognised_tokens[5].position.column);

        CHECK_EQ(token_type::T_INT, recognised_tokens[6].type);
        CHECK_EQ(3, recognised_tokens[6].position.line);
        CHECK_EQ(2, recognised_tokens[6].position.column);
        REQUIRE_UNARY(holds_alternative<int>(recognised_tokens[6].value));
        CHECK_EQ(5, std::get<int>(recognised_tokens[6].value));

        CHECK_EQ(token_type::T_MINUS, recognised_tokens[7].type);
        CHECK_EQ(4, recognised_tokens[7].position.line);
        CHECK_EQ(1, recognised_tokens[7].position.column);

        CHECK_EQ(token_type::T_DOUBLE, recognised_tokens[8].type);
        CHECK_EQ(4, recognised_tokens[8].position.line);
        CHECK_EQ(2, recognised_tokens[8].position.column);
        REQUIRE_UNARY(holds_alternative<double>(recognised_tokens[8].value));
        CHECK_EQ(0.07, std::get<double>(recognised_tokens[8].value));

        CHECK_EQ(token_type::T_END, recognised_tokens[9].type);
        CHECK_EQ(5, recognised_tokens[9].position.line);
        CHECK_EQ(1, recognised_tokens[9].position.column);
    }

    SUBCASE("Numbers too large") {
        input_chars << "9876543210\n98765432101\n9876543210.12\n17.9876543210\n";
        REQUIRE_NOTHROW(recogniseAllTokens());
        REQUIRE_EQ(8, recognised_tokens.size());

        CHECK_EQ(token_type::T_NUMBER_TOO_LARGE, recognised_tokens[0].type);
        CHECK_EQ(1, recognised_tokens[0].position.line);
        CHECK_EQ(1, recognised_tokens[0].position.column);

        CHECK_EQ(token_type::T_NUMBER_TOO_LARGE, recognised_tokens[1].type);
        CHECK_EQ(2, recognised_tokens[1].position.line);
        CHECK_EQ(1, recognised_tokens[1].position.column);

        CHECK_EQ(token_type::T_INT, recognised_tokens[2].type);
        CHECK_EQ(2, recognised_tokens[2].position.line);
        CHECK_EQ(11, recognised_tokens[2].position.column);
        REQUIRE_UNARY(holds_alternative<int>(recognised_tokens[2].value));
        CHECK_EQ(1, std::get<int>(recognised_tokens[2].value));

        CHECK_EQ(token_type::T_NUMBER_TOO_LARGE, recognised_tokens[3].type);
        CHECK_EQ(3, recognised_tokens[3].position.line);
        CHECK_EQ(1, recognised_tokens[3].position.column);

        CHECK_EQ(token_type::T_DOT, recognised_tokens[4].type);
        CHECK_EQ(3, recognised_tokens[4].position.line);
        CHECK_EQ(11, recognised_tokens[4].position.column);

        CHECK_EQ(token_type::T_INT, recognised_tokens[5].type);
        CHECK_EQ(3, recognised_tokens[5].position.line);
        CHECK_EQ(12, recognised_tokens[5].position.column);
        REQUIRE_UNARY(holds_alternative<int>(recognised_tokens[5].value));
        CHECK_EQ(12, std::get<int>(recognised_tokens[5].value));

        CHECK_EQ(token_type::T_NUMBER_TOO_LARGE, recognised_tokens[6].type);
        CHECK_EQ(4, recognised_tokens[6].position.line);
        CHECK_EQ(1, recognised_tokens[6].position.column);

        CHECK_EQ(token_type::T_END, recognised_tokens[7].type);
        CHECK_EQ(5, recognised_tokens[7].position.line);
        CHECK_EQ(1, recognised_tokens[7].position.column);
    }
}

TEST_CASE("Time units recognition") {
    input_chars.clear();
    SUBCASE("[s], [m] and [h]") {
        input_chars << "[s] \n[m] \n[h] \n";
        REQUIRE_NOTHROW(recogniseAllTokens());
        REQUIRE_EQ(4, recognised_tokens.size());

        token_type exp_type = lexer::T_SEC_U;

        for (int i = 1; i <= 3; ++i) {
            CHECK_EQ(exp_type, recognised_tokens[i - 1].type);
            CHECK_EQ(i, recognised_tokens[i - 1].position.line);
            CHECK_EQ(1, recognised_tokens[i - 1].position.column);

            exp_type = (token_type) (exp_type + 1);
        }

        CHECK_EQ(token_type::T_END, recognised_tokens[3].type);
        CHECK_EQ(4, recognised_tokens[3].position.line);
        CHECK_EQ(1, recognised_tokens[3].position.column);
    }

    SUBCASE("Incorrect unit") {
        input_chars << "[x] [h\n";
        REQUIRE_NOTHROW(recogniseAllTokens());
        REQUIRE_EQ(3, recognised_tokens.size());

        CHECK_EQ(token_type::T_UNKNOWN, recognised_tokens[0].type);
        CHECK_EQ(1, recognised_tokens[0].position.line);
        CHECK_EQ(1, recognised_tokens[0].position.column);
        REQUIRE_UNARY(holds_alternative<string>(recognised_tokens[0].value));
        CHECK_EQ("[x]", std::get<string>(recognised_tokens[0].value));

        CHECK_EQ(token_type::T_UNKNOWN, recognised_tokens[1].type);
        CHECK_EQ(1, recognised_tokens[1].position.line);
        CHECK_EQ(5, recognised_tokens[1].position.column);
        REQUIRE_UNARY(holds_alternative<string>(recognised_tokens[1].value));
        CHECK_EQ("[h", std::get<string>(recognised_tokens[1].value));

        CHECK_EQ(token_type::T_END, recognised_tokens[2].type);
        CHECK_EQ(2, recognised_tokens[2].position.line);
        CHECK_EQ(1, recognised_tokens[2].position.column);
    }
}

TEST_CASE("Time period recognition") {
    input_chars.clear();
    input_chars << "[+2:15:01]\n";
    REQUIRE_NOTHROW(recogniseAllTokens());
    REQUIRE_EQ(2, recognised_tokens.size());

    CHECK_EQ(token_type::T_TIME_PERIOD, recognised_tokens[0].type);
    CHECK_EQ(1, recognised_tokens[0].position.line);
    CHECK_EQ(1, recognised_tokens[0].position.column);
    REQUIRE_UNARY(holds_alternative<lexer::TimePeriod>(recognised_tokens[0].value));
    lexer::TimePeriod tp = std::get<lexer::TimePeriod>(recognised_tokens[0].value);
    CHECK_EQ(std::chrono::seconds(1), tp.s);
    CHECK_EQ(std::chrono::minutes(15), tp.m);
    CHECK_EQ(std::chrono::hours(2), tp.h);

    CHECK_EQ(token_type::T_END, recognised_tokens[1].type);
    CHECK_EQ(2, recognised_tokens[1].position.line);
    CHECK_EQ(1, recognised_tokens[1].position.column);
}

TEST_CASE("Time moments recognition") {
    input_chars.clear();

    SUBCASE("Clock") {
        input_chars << "[^18:54:32]\n";
        REQUIRE_NOTHROW(recogniseAllTokens());
        REQUIRE_EQ(2, recognised_tokens.size());

        CHECK_EQ(token_type::T_CLOCK, recognised_tokens[0].type);
        CHECK_EQ(1, recognised_tokens[0].position.line);
        CHECK_EQ(1, recognised_tokens[0].position.column);
        REQUIRE_UNARY(holds_alternative<lexer::TimeMoment>(recognised_tokens[0].value));
        lexer::TimeMoment tm = std::get<lexer::TimeMoment>(recognised_tokens[0].value);
        CHECK_EQ(18, tm.getHour());
        CHECK_EQ(54, tm.getMin());
        CHECK_EQ(32, tm.getSec());

        CHECK_EQ(token_type::T_END, recognised_tokens[1].type);
        CHECK_EQ(2, recognised_tokens[1].position.line);
        CHECK_EQ(1, recognised_tokens[1].position.column);
    }

    SUBCASE("Date") {
        input_chars << "[21/03/2021]\n";
        REQUIRE_NOTHROW(recogniseAllTokens());
        REQUIRE_EQ(2, recognised_tokens.size());

        CHECK_EQ(token_type::T_DATE, recognised_tokens[0].type);
        CHECK_EQ(1, recognised_tokens[0].position.line);
        CHECK_EQ(1, recognised_tokens[0].position.column);
        REQUIRE_UNARY(holds_alternative<lexer::TimeMoment>(recognised_tokens[0].value));
        lexer::TimeMoment tm = std::get<lexer::TimeMoment>(recognised_tokens[0].value);
        CHECK_EQ(21, tm.getDay());
        CHECK_EQ(3, tm.getMonth());
        CHECK_EQ(2021, tm.getYear());

        CHECK_EQ(token_type::T_END, recognised_tokens[1].type);
        CHECK_EQ(2, recognised_tokens[1].position.line);
        CHECK_EQ(1, recognised_tokens[1].position.column);
    }

    SUBCASE("Timestamp") {
        input_chars << "[21/03/2021 18:54:32]\n";
        REQUIRE_NOTHROW(recogniseAllTokens());
        REQUIRE_EQ(2, recognised_tokens.size());

        CHECK_EQ(token_type::T_TIMESTAMP, recognised_tokens[0].type);
        CHECK_EQ(1, recognised_tokens[0].position.line);
        CHECK_EQ(1, recognised_tokens[0].position.column);
        REQUIRE_UNARY(holds_alternative<lexer::TimeMoment>(recognised_tokens[0].value));
        lexer::TimeMoment tm = std::get<lexer::TimeMoment>(recognised_tokens[0].value);
        CHECK_EQ(21, tm.getDay());
        CHECK_EQ(3, tm.getMonth());
        CHECK_EQ(2021, tm.getYear());
        CHECK_EQ(18, tm.getHour());
        CHECK_EQ(54, tm.getMin());
        CHECK_EQ(32, tm.getSec());

        CHECK_EQ(token_type::T_END, recognised_tokens[1].type);
        CHECK_EQ(2, recognised_tokens[1].position.line);
        CHECK_EQ(1, recognised_tokens[1].position.column);
    }
}

TEST_CASE("Operators recognition") {
    input_chars.clear();
    input_chars << "= \n+ \n- \n* \n/ \n| \n& \n== \n=\\= \n> \n>= \n< \n<= \n";
    REQUIRE_NOTHROW(recogniseAllTokens());
    REQUIRE_EQ(14, recognised_tokens.size());

    token_type exp_type = lexer::T_ASSIGN;

    for (int i = 1; i <= 13; ++i) {
        CHECK_EQ(exp_type, recognised_tokens[i - 1].type);
        CHECK_EQ(i, recognised_tokens[i - 1].position.line);
        CHECK_EQ(1, recognised_tokens[i - 1].position.column);

        exp_type = (token_type) (exp_type + 1);
    }

    CHECK_EQ(token_type::T_END, recognised_tokens[13].type);
    CHECK_EQ(14, recognised_tokens[13].position.line);
    CHECK_EQ(1, recognised_tokens[13].position.column);
}

TEST_CASE("Brackets recognition") {
    input_chars.clear();
    input_chars << "({ })";
    REQUIRE_NOTHROW(recogniseAllTokens());
    REQUIRE_EQ(5, recognised_tokens.size());

    CHECK_EQ(token_type::T_PARENTHESES_1, recognised_tokens[0].type);
    CHECK_EQ(1, recognised_tokens[0].position.line);
    CHECK_EQ(1, recognised_tokens[0].position.column);

    CHECK_EQ(token_type::T_BRACE_1, recognised_tokens[1].type);
    CHECK_EQ(1, recognised_tokens[1].position.line);
    CHECK_EQ(2, recognised_tokens[1].position.column);

    CHECK_EQ(token_type::T_BRACE_2, recognised_tokens[2].type);
    CHECK_EQ(1, recognised_tokens[2].position.line);
    CHECK_EQ(4, recognised_tokens[2].position.column);

    CHECK_EQ(token_type::T_PARENTHESES_2, recognised_tokens[3].type);
    CHECK_EQ(1, recognised_tokens[3].position.line);
    CHECK_EQ(5, recognised_tokens[3].position.column);

    CHECK_EQ(token_type::T_END, recognised_tokens[4].type);
    CHECK_EQ(1, recognised_tokens[4].position.line);
    CHECK_EQ(6, recognised_tokens[4].position.column);
}

TEST_CASE("Commas and dots recognition") {
    input_chars.clear();
    input_chars << ". ,";
    REQUIRE_NOTHROW(recogniseAllTokens());
    REQUIRE_EQ(3, recognised_tokens.size());

    CHECK_EQ(token_type::T_DOT, recognised_tokens[0].type);
    CHECK_EQ(1, recognised_tokens[0].position.line);
    CHECK_EQ(1, recognised_tokens[0].position.column);

    CHECK_EQ(token_type::T_COMMA, recognised_tokens[1].type);
    CHECK_EQ(1, recognised_tokens[1].position.line);
    CHECK_EQ(3, recognised_tokens[1].position.column);

    CHECK_EQ(token_type::T_END, recognised_tokens[2].type);
    CHECK_EQ(1, recognised_tokens[2].position.line);
    CHECK_EQ(4, recognised_tokens[2].position.column);
}

TEST_CASE("Skipping comments test") {
    input_chars.clear();
    input_chars << "#Comment 1### var # Comment\n2 [s]##";
    REQUIRE_NOTHROW(recogniseAllTokens());
    REQUIRE_EQ(2, recognised_tokens.size());
    CHECK_EQ(token_type::T_IDENTIFIER, recognised_tokens[0].type);
    CHECK_EQ(1, recognised_tokens[0].position.line);
    CHECK_EQ(15, recognised_tokens[0].position.column);
    REQUIRE_UNARY(holds_alternative<string>(recognised_tokens[0].value));
    CHECK_EQ("var", std::get<string>(recognised_tokens[0].value));

    CHECK_EQ(token_type::T_END, recognised_tokens[1].type);
    CHECK_EQ(2, recognised_tokens[1].position.line);
    CHECK_EQ(8, recognised_tokens[1].position.column);
}

TEST_SUITE_END;