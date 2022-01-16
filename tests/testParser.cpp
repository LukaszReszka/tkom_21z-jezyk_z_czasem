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
                     "---a98\n"
                     "---b_1\n"
                     "---c\n";

        CHECK_EQ(right_tree, getTree(code));
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
}

TEST_CASE("Assign operator") {
    SUBCASE("Assigning int number") {
        code = "a = 2";
        right_tree = "PROGRAM ROOT\n"
                     "-Operator ASSIGN\n"
                     "--First Operand:\n"
                     "---VARIABLE: a\n"
                     "--Second Operand:\n"
                     "---INT: 2\n";

        CHECK_EQ(right_tree, getTree(code));
    }

    SUBCASE("Assigning negative int number") {
        code = "a = -9";
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
        code = "pi_numb = 3.14";
        right_tree = "PROGRAM ROOT\n"
                     "-Operator ASSIGN\n"
                     "--First Operand:\n"
                     "---VARIABLE: pi_numb\n"
                     "--Second Operand:\n"
                     "---DOUBLE: 3.140000\n";

        CHECK_EQ(right_tree, getTree(code));
    }

    SUBCASE("Assigning negative double number") {
        code = "negative_PI = -3.14";
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
        code = "a = b";
        right_tree = "PROGRAM ROOT\n"
                     "-Operator ASSIGN\n"
                     "--First Operand:\n"
                     "---VARIABLE: a\n"
                     "--Second Operand:\n"
                     "---VARIABLE: b\n";

        CHECK_EQ(right_tree, getTree(code));
    }

    SUBCASE("Assigning result from function call") {
        code = "a = .func(arg1, arg2)";
        right_tree = "PROGRAM ROOT\n"
                     "-Operator ASSIGN\n"
                     "--First Operand:\n"
                     "---VARIABLE: a\n"
                     "--Second Operand:\n"
                     "---Function Call\n"
                     "----Name: func\n"
                     "----Arguments:\n"
                     "-----arg1\n"
                     "-----arg2\n";

        CHECK_EQ(right_tree, getTree(code));
    }

    SUBCASE("Assigning time period") {
        code = "a = [+2:30:54]";
        right_tree = "PROGRAM ROOT\n"
                     "-Operator ASSIGN\n"
                     "--First Operand:\n"
                     "---VARIABLE: a\n"
                     "--Second Operand:\n"
                     "---TIME_PERIOD[s]: 9054\n";

        CHECK_EQ(right_tree, getTree(code));
    }

    SUBCASE("Assigning time moment - clock") {
        code = "a = [^12:59:22]";
        right_tree = "PROGRAM ROOT\n"
                     "-Operator ASSIGN\n"
                     "--First Operand:\n"
                     "---VARIABLE: a\n"
                     "--Second Operand:\n"
                     "---CLOCK: 12:59:22\n";

        CHECK_EQ(right_tree, getTree(code));
    }

    SUBCASE("Assigning time moment - date") {
        code = "a = [13/12/2021]";
        right_tree = "PROGRAM ROOT\n"
                     "-Operator ASSIGN\n"
                     "--First Operand:\n"
                     "---VARIABLE: a\n"
                     "--Second Operand:\n"
                     "---DATE: 13/12/2021\n";

        CHECK_EQ(right_tree, getTree(code));
    }

    SUBCASE("Assigning time moment - timestamp") {
        code = "a = [24/12/2021 18:15:40]";
        right_tree = "PROGRAM ROOT\n"
                     "-Operator ASSIGN\n"
                     "--First Operand:\n"
                     "---VARIABLE: a\n"
                     "--Second Operand:\n"
                     "---TIMESTAMP: 24/12/2021 18:15:40\n";

        CHECK_EQ(right_tree, getTree(code));
    }

    SUBCASE("Assigning expression - multiplication") {
        code = "a = [h]3 * 2";
        right_tree = "PROGRAM ROOT\n"
                     "-Operator ASSIGN\n"
                     "--First Operand:\n"
                     "---VARIABLE: a\n"
                     "--Second Operand:\n"
                     "---Operator MULTIPLY\n"
                     "----First Operand:\n"
                     "-----HOURS(int): 3\n"
                     "----Second Operand:\n"
                     "-----INT: 2\n";

        CHECK_EQ(right_tree, getTree(code));
    }

    SUBCASE("Assigning expression - division") {
        code = "a = [m]60 / 2";
        right_tree = "PROGRAM ROOT\n"
                     "-Operator ASSIGN\n"
                     "--First Operand:\n"
                     "---VARIABLE: a\n"
                     "--Second Operand:\n"
                     "---Operator DIVIDE\n"
                     "----First Operand:\n"
                     "-----MINUTES(int): 60\n"
                     "----Second Operand:\n"
                     "-----INT: 2\n";

        CHECK_EQ(right_tree, getTree(code));
    }
}


TEST_SUITE_END;