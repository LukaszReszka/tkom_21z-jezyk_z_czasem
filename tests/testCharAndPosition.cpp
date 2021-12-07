#include "../libs/doctest/include/doctest.h"
#include "../src/codeSource/charAndPosition.h"


TEST_SUITE_BEGIN("CharAndPosition class tests");

TEST_CASE("constructors tests") {

    SUBCASE("not EOF constructor") {
        code_source::CharAndPosition test_struct('a', 1, 2);
        CHECK_EQ('a', test_struct.readChar);
        CHECK_EQ(1, test_struct.line);
        CHECK_EQ(2, test_struct.column);
        CHECK_EQ(false, test_struct.isEndOfText);
    }

    SUBCASE("EOF constructor") {
        code_source::CharAndPosition test_struct(3, 4);
        CHECK_EQ(3, test_struct.line);
        CHECK_EQ(4, test_struct.column);
        CHECK_EQ(true, test_struct.isEndOfText);
    }
}

TEST_SUITE_END;