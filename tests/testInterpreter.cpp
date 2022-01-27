#include "../libs/doctest/include/doctest.h"
#include "../interpreter/interpreter.h"
#include <sstream>

TEST_SUITE_BEGIN("Interpreter tests");

std::string getResult(std::string code) {
    std::stringstream code_to_test(code);
    interpreter::Interpreter interpreter(code_to_test);
    std::stringstream ss;
    auto cout_buff = std::cout.rdbuf();
    std::cout.rdbuf(ss.rdbuf());
    interpreter.executeProgram();
    std::cout.rdbuf(cout_buff);
    return ss.str();
}

TEST_CASE("Functionality tests") {
    std::string code, expected_result;

    SUBCASE("If statement") {
        code = "if(1 > 2)"
               "{SHOW(\"PRAWDA\")}"
               "else"
               "{SHOW(\"FALSZ\")}";

        expected_result = "FALSZ";

        CHECK_EQ(getResult(code), expected_result);
    }

    SUBCASE("If statement 2") {
        code = "a = 1,"
               "if(a > 2)"
               "{a = a + 1,}"
               "else"
               "{a = a - 1,}"
               "SHOW(a)";

        expected_result = "0";

        CHECK_EQ(getResult(code), expected_result);
    }

    SUBCASE("If statement 3") {
        code = "a = 1 + 3,"
               "if(a > 0 & a < 4)"
               "{SHOW(\"PRAWDA\")}"
               "else"
               "{SHOW(\"FALSZ\")}";

        expected_result = "FALSZ";

        CHECK_EQ(getResult(code), expected_result);
    }

    SUBCASE("While loop") {
        code = "a = 1,"
               "while(a < 2)"
               "{"
               "a = a + 1,"
               "}"
               "SHOW(a)";

        expected_result = "2";

        CHECK_EQ(getResult(code), expected_result);
    }

    SUBCASE("While loop 2") {
        code = "a = 1,"
               "while(a > 0 & a < 5)"
               "{"
               "a = a - 1,"
               "}"
               "SHOW(a)";

        expected_result = "0";

        CHECK_EQ(getResult(code), expected_result);
    }

    SUBCASE("FUNC DEF and CALL") {
        code = "FUNC zwrocIleSekundTemu(data)"
               "{"
               "dzis = [28/01/2022],"
               "RET(dzis - data)"
               "}"
               "dataUrodzin = [01/01/2000],"
               "ilosc_sekund = .zwrocIleSekundTemu(dataUrodzin),"
               "SHOW(\"Ilosc przezytych sekund to \", ilosc_sekund)";

        expected_result = "Ilosc przezytych sekund to 696643200s";

        CHECK_EQ(getResult(code), expected_result);
    }

    SUBCASE("FUNC DEF and CALL 2") {
        code = "FUNC zwrocSzczescian(liczba)"
               "{"
               "RET(liczba*liczba*liczba)"
               "}"
               "x = 2,"
               "szescian = .zwrocSzczescian(x),"
               "SHOW(szescian)";

        expected_result = "8";

        CHECK_EQ(getResult(code), expected_result);
    }
}

TEST_SUITE_END;