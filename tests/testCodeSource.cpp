#include <sstream>
#include "../libs/doctest/include/doctest.h"

#include "../src/codeSource.h"

TEST_SUITE_BEGIN("CodeSource class tests");

TEST_CASE("getNextChar() method test - code from file") {

    CharAndPosition test_struct('a', 1, 2);
    CHECK_EQ('a', test_struct.readChar);
    CHECK_EQ(1, test_struct.line);
    CHECK_EQ(2, test_struct.column);
    CHECK_EQ(false, test_struct.isEndOfText);

}

TEST_CASE("getNextChar() method test - code from terminal") {
    std::string code = "ab c; \n x^q\n\n^q";
    std::stringstream user_input_mock(code);
    CodeSource source(user_input_mock);

//    while (true) {
//        CharAndPosition res = source->getNextChar();
//        if (res.isEndOfText) {
//            std::cout << "EOF: " << res.isEndOfText << " L: " << res.line << " C: " << res.column << std::endl;
//            break;
//        }
//        std::cout << res.readChar << " L: " << res.line << " C: " << res.column << std::endl;
//    }

}

TEST_SUITE_END;
