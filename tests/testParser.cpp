#include "../libs/doctest/include/doctest.h"
#include "../src/parser/parser.h"
#include <sstream>

TEST_SUITE_BEGIN("Parser tests - building program tree");

std::string getTree(const std::string &code) {
    std::stringstream code_to_test(code);
    code_source::CodeSource source(code_to_test);
    lexer::Lexer lexer(source);
    parser::Parser parser(lexer, nullptr);
    unique_ptr<parser::ProgramTree> tree = std::move(parser.parseProgram());
    return tree->toString(0);
}

std::string code, right_tree;

TEST_CASE("Function call") {
    SUBCASE("With no arguments") {
        code = ".func()";
        right_tree = "PROGRAM ROOT\n"
                     "-Function Call\n"
                     "--Name: func\n"
                     "--Arguments:\n";

        CHECK_EQ(right_tree, getTree(code));
    }

    SUBCASE("With arguments") {
        code = ".anotherFunc(a98, b_1, c) #inna funkcja#";
        right_tree = "PROGRAM ROOT\n"
                     "-Function Call\n"
                     "--Name: anotherFunc\n"
                     "--Arguments:\n"
                     "---VARIABLE: a98\n"
                     "---VARIABLE: b_1\n"
                     "---VARIABLE: c\n";

        CHECK_EQ(right_tree, getTree(code));
    }

    SUBCASE("Missing dot at the beginning") {
        code = "fun(x, y, z)";
        CHECK_THROWS_WITH(getTree(code), "Wrong operator - expected \"=\"");
    }
}

TEST_CASE("Function definition") {
    SUBCASE("No arguments and empty body") {
        code = "FUNC fun() {}";
        right_tree = "PROGRAM ROOT\n"
                     "-Function Definition\n"
                     "--Name: fun\n"
                     "--Parameters:\n"
                     "--Function Body:\n";

        CHECK_EQ(right_tree, getTree(code));
    }

    SUBCASE("With arguments and instructions in body") {
        code = "FUNC fun(a, b) { SHOW(\"test definiowania funkcji\")}";
        right_tree = "PROGRAM ROOT\n"
                     "-Function Definition\n"
                     "--Name: fun\n"
                     "--Parameters:\n"
                     "---a\n"
                     "---b\n"
                     "--Function Body:\n"
                     "---SHOW\n"
                     "----Arguments:\n"
                     "-----STRING: test definiowania funkcji\n";

        CHECK_EQ(right_tree, getTree(code));
    }
}

TEST_CASE("SHOW Function") {
    SUBCASE("With string argument") {
        code = "SHOW(\"Ala ma kota\")";
        right_tree = "PROGRAM ROOT\n"
                     "-SHOW\n"
                     "--Arguments:\n"
                     "---STRING: Ala ma kota\n";

        CHECK_EQ(right_tree, getTree(code));
    }

    SUBCASE("With string arguments - with escaping \"") {
        code = R"(SHOW("He said \"no\"", "She replied \"yes\""))";
        right_tree = "PROGRAM ROOT\n"
                     "-SHOW\n"
                     "--Arguments:\n"
                     "---STRING: He said \"no\"\n"
                     "---STRING: She replied \"yes\"\n";

        CHECK_EQ(right_tree, getTree(code));
    }

    SUBCASE("Empty Show") {
        code = "SHOW()";
        CHECK_THROWS_WITH(getTree(code), "Expected literal");
    }
}

TEST_CASE("Assign operator") {
    SUBCASE("Assigning int number") {
        code = "a = 2,";
        right_tree = "PROGRAM ROOT\n"
                     "-Operator ASSIGN\n"
                     "--First Operand:\n"
                     "---VARIABLE: a\n"
                     "--Second Operand:\n"
                     "---INT: 2\n";

        CHECK_EQ(right_tree, getTree(code));
    }

    SUBCASE("Assigning negative int number") {
        code = "a = -9,";
        right_tree = "PROGRAM ROOT\n"
                     "-Operator ASSIGN\n"
                     "--First Operand:\n"
                     "---VARIABLE: a\n"
                     "--Second Operand:\n"
                     "---Operator UNARY_MINUS\n"
                     "----First Operand:\n"
                     "-----INT: 9\n";

        CHECK_EQ(right_tree, getTree(code));
    }

    SUBCASE("Assigning double number") {
        code = "pi_numb = 3.14,";
        right_tree = "PROGRAM ROOT\n"
                     "-Operator ASSIGN\n"
                     "--First Operand:\n"
                     "---VARIABLE: pi_numb\n"
                     "--Second Operand:\n"
                     "---DOUBLE: 3.140000\n";

        CHECK_EQ(right_tree, getTree(code));
    }

    SUBCASE("Assigning negative double number") {
        code = "negative_PI = -3.14,";
        right_tree = "PROGRAM ROOT\n"
                     "-Operator ASSIGN\n"
                     "--First Operand:\n"
                     "---VARIABLE: negative_PI\n"
                     "--Second Operand:\n"
                     "---Operator UNARY_MINUS\n"
                     "----First Operand:\n"
                     "-----DOUBLE: 3.140000\n";

        CHECK_EQ(right_tree, getTree(code));
    }

    SUBCASE("Assigning another variable") {
        code = "a = b,";
        right_tree = "PROGRAM ROOT\n"
                     "-Operator ASSIGN\n"
                     "--First Operand:\n"
                     "---VARIABLE: a\n"
                     "--Second Operand:\n"
                     "---VARIABLE: b\n";

        CHECK_EQ(right_tree, getTree(code));
    }

    SUBCASE("Assigning result from function call") {
        code = "a = .func(arg1, arg2),";
        right_tree = "PROGRAM ROOT\n"
                     "-Operator ASSIGN\n"
                     "--First Operand:\n"
                     "---VARIABLE: a\n"
                     "--Second Operand:\n"
                     "---Function Call\n"
                     "----Name: func\n"
                     "----Arguments:\n"
                     "-----VARIABLE: arg1\n"
                     "-----VARIABLE: arg2\n";

        CHECK_EQ(right_tree, getTree(code));
    }

    SUBCASE("Assigning time period") {
        code = "a = [+2:30:54],";
        right_tree = "PROGRAM ROOT\n"
                     "-Operator ASSIGN\n"
                     "--First Operand:\n"
                     "---VARIABLE: a\n"
                     "--Second Operand:\n"
                     "---TIME_PERIOD[s]: 9054s\n";

        CHECK_EQ(right_tree, getTree(code));
    }

    SUBCASE("Assigning time moment - clock") {
        code = "a = [^12:59:22],";
        right_tree = "PROGRAM ROOT\n"
                     "-Operator ASSIGN\n"
                     "--First Operand:\n"
                     "---VARIABLE: a\n"
                     "--Second Operand:\n"
                     "---CLOCK: 12:59:22\n";

        CHECK_EQ(right_tree, getTree(code));
    }

    SUBCASE("Assigning time moment - date") {
        code = "a = [13/12/2021],";
        right_tree = "PROGRAM ROOT\n"
                     "-Operator ASSIGN\n"
                     "--First Operand:\n"
                     "---VARIABLE: a\n"
                     "--Second Operand:\n"
                     "---DATE: 13/12/2021\n";

        CHECK_EQ(right_tree, getTree(code));
    }

    SUBCASE("Assigning time moment - timestamp") {
        code = "a = [24/12/2021 18:15:40],";
        right_tree = "PROGRAM ROOT\n"
                     "-Operator ASSIGN\n"
                     "--First Operand:\n"
                     "---VARIABLE: a\n"
                     "--Second Operand:\n"
                     "---TIMESTAMP: 24/12/2021 18:15:40\n";

        CHECK_EQ(right_tree, getTree(code));
    }

    SUBCASE("Assigning expression - multiplication") {
        code = "a = [h]3 * 2,";
        right_tree = "PROGRAM ROOT\n"
                     "-Operator ASSIGN\n"
                     "--First Operand:\n"
                     "---VARIABLE: a\n"
                     "--Second Operand:\n"
                     "---Operator MULTIPLY\n"
                     "----First Operand:\n"
                     "-----HOURS(int): 3h\n"
                     "----Second Operand:\n"
                     "-----INT: 2\n";

        CHECK_EQ(right_tree, getTree(code));
    }

    SUBCASE("Assigning expression - division") {
        code = "a = [m]60 / 2,";
        right_tree = "PROGRAM ROOT\n"
                     "-Operator ASSIGN\n"
                     "--First Operand:\n"
                     "---VARIABLE: a\n"
                     "--Second Operand:\n"
                     "---Operator DIVIDE\n"
                     "----First Operand:\n"
                     "-----MINUTES(int): 60m\n"
                     "----Second Operand:\n"
                     "-----INT: 2\n";

        CHECK_EQ(right_tree, getTree(code));
    }

    SUBCASE("assigning to function call") {
        code = ".func() = 1 + 3,";
        CHECK_THROWS_WITH(getTree(code), "Unrecognised instruction");
    }

    SUBCASE("missing closing comma") {
        code = "a = 1";
        CHECK_THROWS_WITH(getTree(code), "Lack of \",\"");
    }
}

TEST_CASE("If statement") {

    SUBCASE("Only if") {
        code = "if(a >= -[s]10)"
               "{a = a + [s]1,}";

        right_tree = "PROGRAM ROOT\n"
                     "-IF\n"
                     "--Condition:\n"
                     "---Operator GREATER_EQUAL\n"
                     "----First Operand:\n"
                     "-----VARIABLE: a\n"
                     "----Second Operand:\n"
                     "-----Operator UNARY_MINUS\n"
                     "------First Operand:\n"
                     "-------SECONDS(int): 10s\n"
                     "--Body:\n"
                     "---Operator ASSIGN\n"
                     "----First Operand:\n"
                     "-----VARIABLE: a\n"
                     "----Second Operand:\n"
                     "-----Operator PLUS\n"
                     "------First Operand:\n"
                     "-------VARIABLE: a\n"
                     "------Second Operand:\n"
                     "-------SECONDS(int): 1s\n";

        CHECK_EQ(right_tree, getTree(code));
    }

    SUBCASE("If with elif") {
        code = "if(a >= -[s]10)"
               "{a = a + [s]1,}"
               "elif(b =\\= [28/01/2022])"
               "{SHOW(b)}";

        right_tree = "PROGRAM ROOT\n"
                     "-IF\n"
                     "--Condition:\n"
                     "---Operator GREATER_EQUAL\n"
                     "----First Operand:\n"
                     "-----VARIABLE: a\n"
                     "----Second Operand:\n"
                     "-----Operator UNARY_MINUS\n"
                     "------First Operand:\n"
                     "-------SECONDS(int): 10s\n"
                     "--Body:\n"
                     "---Operator ASSIGN\n"
                     "----First Operand:\n"
                     "-----VARIABLE: a\n"
                     "----Second Operand:\n"
                     "-----Operator PLUS\n"
                     "------First Operand:\n"
                     "-------VARIABLE: a\n"
                     "------Second Operand:\n"
                     "-------SECONDS(int): 1s\n"
                     "---ELIF\n"
                     "----Condition:\n"
                     "-----Operator NOT_EQUAL\n"
                     "------First Operand:\n"
                     "-------VARIABLE: b\n"
                     "------Second Operand:\n"
                     "-------DATE: 28/01/2022\n"
                     "----Body:\n"
                     "-----SHOW\n"
                     "------Arguments:\n"
                     "-------VARIABLE: b\n";

        CHECK_EQ(right_tree, getTree(code));
    }

    SUBCASE("If with else") {
        code = "if(a >= -[s]10)"
               "{a = a + [s]1,}"
               "else"
               "{a = b,}";

        right_tree = "PROGRAM ROOT\n"
                     "-IF\n"
                     "--Condition:\n"
                     "---Operator GREATER_EQUAL\n"
                     "----First Operand:\n"
                     "-----VARIABLE: a\n"
                     "----Second Operand:\n"
                     "-----Operator UNARY_MINUS\n"
                     "------First Operand:\n"
                     "-------SECONDS(int): 10s\n"
                     "--Body:\n"
                     "---Operator ASSIGN\n"
                     "----First Operand:\n"
                     "-----VARIABLE: a\n"
                     "----Second Operand:\n"
                     "-----Operator PLUS\n"
                     "------First Operand:\n"
                     "-------VARIABLE: a\n"
                     "------Second Operand:\n"
                     "-------SECONDS(int): 1s\n"
                     "---ELIF\n"
                     "----Condition:\n"
                     "-----BOOL: 1\n"
                     "----Body:\n"
                     "-----Operator ASSIGN\n"
                     "------First Operand:\n"
                     "-------VARIABLE: a\n"
                     "------Second Operand:\n"
                     "-------VARIABLE: b\n";

        CHECK_EQ(right_tree, getTree(code));
    }

    SUBCASE("If with elifs and else") {
        code = "if(a < b)"
               "{a = b,}"
               "elif(a == b)"
               "{a = b + 1,}"
               "elif(a >= b + 1)"
               "{a = 0,}"
               "else"
               "{a = 1,}";

        right_tree = "PROGRAM ROOT\n"
                     "-IF\n"
                     "--Condition:\n"
                     "---Operator LESS\n"
                     "----First Operand:\n"
                     "-----VARIABLE: a\n"
                     "----Second Operand:\n"
                     "-----VARIABLE: b\n"
                     "--Body:\n"
                     "---Operator ASSIGN\n"
                     "----First Operand:\n"
                     "-----VARIABLE: a\n"
                     "----Second Operand:\n"
                     "-----VARIABLE: b\n"
                     "---ELIF\n"
                     "----Condition:\n"
                     "-----Operator EQUAL\n"
                     "------First Operand:\n"
                     "-------VARIABLE: a\n"
                     "------Second Operand:\n"
                     "-------VARIABLE: b\n"
                     "----Body:\n"
                     "-----Operator ASSIGN\n"
                     "------First Operand:\n"
                     "-------VARIABLE: a\n"
                     "------Second Operand:\n"
                     "-------Operator PLUS\n"
                     "--------First Operand:\n"
                     "---------VARIABLE: b\n"
                     "--------Second Operand:\n"
                     "---------INT: 1\n"
                     "---ELIF\n"
                     "----Condition:\n"
                     "-----Operator GREATER_EQUAL\n"
                     "------First Operand:\n"
                     "-------VARIABLE: a\n"
                     "------Second Operand:\n"
                     "-------Operator PLUS\n"
                     "--------First Operand:\n"
                     "---------VARIABLE: b\n"
                     "--------Second Operand:\n"
                     "---------INT: 1\n"
                     "----Body:\n"
                     "-----Operator ASSIGN\n"
                     "------First Operand:\n"
                     "-------VARIABLE: a\n"
                     "------Second Operand:\n"
                     "-------INT: 0\n"
                     "---ELIF\n"
                     "----Condition:\n"
                     "-----BOOL: 1\n"
                     "----Body:\n"
                     "-----Operator ASSIGN\n"
                     "------First Operand:\n"
                     "-------VARIABLE: a\n"
                     "------Second Operand:\n"
                     "-------INT: 1\n";

        CHECK_EQ(right_tree, getTree(code));
    }

    SUBCASE("else - adding condition") {
        code = "if(1 == 2) {} else (2 == 2) {}";
        CHECK_THROWS_WITH(getTree(code), "Lack of \"{\"");
    }

    SUBCASE("elif - without condiiton") {
        code = "if(1 == 2) {} elif { a = 1 + 3,}";
        CHECK_THROWS_WITH(getTree(code), "Lack of \"(\"");
    }

}

TEST_CASE("RET expression") {
    SUBCASE("RET variable") {
        code = "RET(a)";

        right_tree = "PROGRAM ROOT\n"
                     "-RET\n"
                     "--VARIABLE: a\n";

        CHECK_EQ(right_tree, getTree(code));
    }

    SUBCASE("RET expression") {
        code = "RET(a + 1 / .func())";

        right_tree = "PROGRAM ROOT\n"
                     "-RET\n"
                     "--Operator PLUS\n"
                     "---First Operand:\n"
                     "----VARIABLE: a\n"
                     "---Second Operand:\n"
                     "----Operator DIVIDE\n"
                     "-----First Operand:\n"
                     "------INT: 1\n"
                     "-----Second Operand:\n"
                     "------Function Call\n"
                     "-------Name: func\n"
                     "-------Arguments:\n";

        CHECK_EQ(right_tree, getTree(code));
    }
}

TEST_CASE("While loop") {
    SUBCASE("while with simple condition and empty body") {
        code = "while(1 == 2) {}";

        right_tree = "PROGRAM ROOT\n"
                     "-WHILE\n"
                     "--Condition:\n"
                     "---Operator EQUAL\n"
                     "----First Operand:\n"
                     "-----INT: 1\n"
                     "----Second Operand:\n"
                     "-----INT: 2\n"
                     "--Body:\n";

        CHECK_EQ(right_tree, getTree(code));
    }

    SUBCASE("ordinary while") {
        code = "while(a < b & a > c)"
               "{"
               "a = b - c,"
               "SHOW(a)"
               "}";

        right_tree = "PROGRAM ROOT\n"
                     "-WHILE\n"
                     "--Condition:\n"
                     "---Operator AND\n"
                     "----First Operand:\n"
                     "-----Operator LESS\n"
                     "------First Operand:\n"
                     "-------VARIABLE: a\n"
                     "------Second Operand:\n"
                     "-------VARIABLE: b\n"
                     "----Second Operand:\n"
                     "-----Operator GREATER\n"
                     "------First Operand:\n"
                     "-------VARIABLE: a\n"
                     "------Second Operand:\n"
                     "-------VARIABLE: c\n"
                     "--Body:\n"
                     "---Operator ASSIGN\n"
                     "----First Operand:\n"
                     "-----VARIABLE: a\n"
                     "----Second Operand:\n"
                     "-----Operator MINUS\n"
                     "------First Operand:\n"
                     "-------VARIABLE: b\n"
                     "------Second Operand:\n"
                     "-------VARIABLE: c\n"
                     "---SHOW\n"
                     "----Arguments:\n"
                     "-----VARIABLE: a\n";

        CHECK_EQ(right_tree, getTree(code));
    }

    SUBCASE("while - lack of \")\"") {
        code = "while(1 == 2 {}";
        CHECK_THROWS_WITH(getTree(code), "Lack of \")\"");
    }

    SUBCASE("while - assigning in condition") {
        code = "while(1 = 2) {}";
        CHECK_THROWS_WITH(getTree(code), "Wrong operator - expected comparison operator");
    }
}

TEST_SUITE_END;