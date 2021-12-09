#include <sstream>
#include "../libs/doctest/include/doctest.h"
#include "../src/codeSource/codeSource.h"


TEST_SUITE_BEGIN("CodeSource class tests");

TEST_CASE("getNextChar() method test - code from file") {
    int lin = 1, col = 1;
    std::fstream source_file;
    std::string file_name = "test_source.txt";

    source_file.open(file_name, std::ios::out);
    REQUIRE_UNARY_FALSE(source_file.fail());
    std::string code = "ab ; \n x\n\n";
    source_file << code;
    source_file.close();

    code_source::CodeSource *source;
    REQUIRE_NOTHROW(source = new code_source::CodeSource(file_name));

    for (int i = 0; i < 10; ++i) {
        code_source::CharAndPosition singleChar = source->getNextChar();
        CHECK_EQ(code[i], singleChar.value);
        CHECK_EQ(lin, singleChar.line);
        CHECK_EQ(col, singleChar.column);
        CHECK_EQ(false, singleChar.isEndOfText);
        if (code[i] == '\n') {
            col = 1;
            ++lin;
        } else {
            ++col;
        }
    }

    code_source::CharAndPosition singleChar = source->getNextChar();
    CHECK_EQ(4, singleChar.line);
    CHECK_EQ(1, singleChar.column);
    CHECK_EQ(true, singleChar.isEndOfText);

    delete source;
    remove(file_name.c_str());
}

TEST_CASE("getNextChar() method test - code from terminal") {
    int lin = 1, col = 1;
    std::string code = "ab ; \n x^q\n\n^q";
    std::stringstream user_input_mock(code);
    code_source::CodeSource source(user_input_mock);
    for (int i = 0; i < 10; ++i) {
        code_source::CharAndPosition singleChar = source.getNextChar();
        CHECK_EQ(code[i], singleChar.value);
        CHECK_EQ(lin, singleChar.line);
        CHECK_EQ(col, singleChar.column);
        CHECK_EQ(false, singleChar.isEndOfText);
        if (i == 4) {
            col = 1;
            ++lin;
            ++i;
        } else {
            ++col;
        }
    }
    code_source::CharAndPosition singleChar = source.getNextChar();
    CHECK_EQ('\0', singleChar.value);
    CHECK_EQ(3, singleChar.line);
    CHECK_EQ(1, singleChar.column);
    CHECK_EQ(false, singleChar.isEndOfText);

    singleChar = source.getNextChar();
    CHECK_EQ(4, singleChar.line);
    CHECK_EQ(1, singleChar.column);
    CHECK_EQ(true, singleChar.isEndOfText);
}

TEST_SUITE_END;
