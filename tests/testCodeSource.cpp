#include <sstream>
#include <fstream>
#include "../libs/doctest/include/doctest.h"
#include "../src/codeSource/codeSource.h"


TEST_SUITE_BEGIN("CodeSource class tests");

TEST_CASE("getNextChar() method test - code from file") {
    int lin = 1, col = 1;
    std::fstream source_file;
    std::string file_name = "test_source.txt";

    REQUIRE_NOTHROW(source_file.open(file_name, std::ios::out));
    REQUIRE_UNARY_FALSE(source_file.fail());
    std::string code = "ab ; \n x\n\n";
    source_file << code;
    source_file.close();

    REQUIRE_NOTHROW(source_file.open(file_name, std::ios::in));
    REQUIRE_UNARY_FALSE(source_file.fail());

    code_source::CodeSource source(source_file);

    for (int i = 0; i < 10; ++i) {
        code_source::CharAndPosition singleChar = source.getNextChar();
        CHECK_EQ(code[i], singleChar.value);
        CHECK_EQ(lin, singleChar.position.line);
        CHECK_EQ(col, singleChar.position.column);
        CHECK_EQ(false, singleChar.isEndOfText);
        if (code[i] == '\n') {
            col = 1;
            ++lin;
        } else {
            ++col;
        }
    }

    code_source::CharAndPosition singleChar = source.getNextChar();
    CHECK_EQ(4, singleChar.position.line);
    CHECK_EQ(1, singleChar.position.column);
    CHECK_EQ(true, singleChar.isEndOfText);

    source_file.close();
    remove(file_name.c_str());
}

TEST_CASE("getNextChar() method test - code from string stream") {
    int lin = 1, col = 1;
    std::string code = "ab ; \n x\n\n";
    std::stringstream input(code);
    code_source::CodeSource source(input);
    for (int i = 0; i < 10; ++i) {
        code_source::CharAndPosition singleChar = source.getNextChar();
        CHECK_EQ(code[i], singleChar.value);
        CHECK_EQ(lin, singleChar.position.line);
        CHECK_EQ(col, singleChar.position.column);
        CHECK_EQ(false, singleChar.isEndOfText);
        if (code[i] == '\n') {
            col = 1;
            ++lin;
        } else {
            ++col;
        }
    }

    code_source::CharAndPosition singleChar = source.getNextChar();
    CHECK_EQ(4, singleChar.position.line);
    CHECK_EQ(1, singleChar.position.column);
    CHECK_EQ(true, singleChar.isEndOfText);
}

TEST_SUITE_END;
