#include "../libs/doctest/include/doctest.h"
#include "../src/parser/parser.h"
#include <sstream>

TEST_SUITE_BEGIN("Parser tests - building AST tree");

std::string getTree(const std::string &code) {
    std::stringstream code_to_test(code);
    code_source::CodeSource source(code_to_test);
    lexer::Lexer lexer(source);
    auto *root = new parser::ProgramNode();
    parser::Parser parser(lexer, root);
    return root->getTextRepresentation(0);
}

std::string code, right_tree;

TEST_CASE("Function call") {
    SUBCASE("With no arguments") {
        code = ".func()";
        right_tree = "PROGRAM ROOT\n"
                     "-Function Call\n"
                     "--Identifier: func\n"
                     "--Function Arguments\n";

        CHECK_EQ(right_tree, getTree(code));
    }

    SUBCASE("With arguments") {
        code = ".anotherFunc(a98, b_1, c) #inna funkcja#";
        right_tree = "PROGRAM ROOT\n"
                     "-Function Call\n"
                     "--Identifier: anotherFunc\n"
                     "--Function Arguments\n"
                     "---Identifier: a98\n"
                     "---Identifier: b_1\n"
                     "---Identifier: c\n";

        CHECK_EQ(right_tree, getTree(code));
    }
}

TEST_CASE("Function definition") {
    SUBCASE("No arguments and empty body") {
        code = "FUNC fun() {}";
        right_tree = "PROGRAM ROOT\n"
                     "-Function Definition\n"
                     "--Identifier: fun\n"
                     "--Function Arguments\n"
                     "--Instructions Block\n";

        CHECK_EQ(right_tree, getTree(code));
    }

    SUBCASE("With arguments and instructions in body") {
        code = "FUNC fun(a, b) { SHOW(\"test definiowania funkcji\")}";
        right_tree = "PROGRAM ROOT\n"
                     "-Function Definition\n"
                     "--Identifier: fun\n"
                     "--Function Arguments\n"
                     "---Identifier: a\n"
                     "---Identifier: b\n"
                     "--Instructions Block\n"
                     "---SHOW Function\n"
                     "----STRING: test definiowania funkcji\n";

        CHECK_EQ(right_tree, getTree(code));
    }
}

TEST_CASE("SHOW Function") {
    SUBCASE("With string argument") {
        code = "SHOW(\"Ala ma kota\")";
        right_tree = "PROGRAM ROOT\n"
                     "-SHOW Function\n"
                     "--STRING: Ala ma kota\n";

        CHECK_EQ(right_tree, getTree(code));
    }

    SUBCASE("With string arguments - with escaping \"") {
        code = R"(SHOW("He said \"no\"", "She replied \"yes\""))";
        right_tree = "PROGRAM ROOT\n"
                     "-SHOW Function\n"
                     "--STRING: He said \"no\"\n"
                     "--STRING: She replied \"yes\"\n";

        CHECK_EQ(right_tree, getTree(code));
    }
}

TEST_CASE("Assign operator") {
    SUBCASE("Assigning int number") {
        code = "a = 2";
        right_tree = "PROGRAM ROOT\n"
                     "-Assign Operation\n"
                     "--INT: 2\n"
                     "-is assigned to\n"
                     "--Identifier: a\n";

        CHECK_EQ(right_tree, getTree(code));
    }

    SUBCASE("Assigning negative int number") {
        code = "a = -9";
        right_tree = "PROGRAM ROOT\n"
                     "-Assign Operation\n"
                     "--Arithmetic NEGATION\n"
                     "---INT: 9\n"
                     "-is assigned to\n"
                     "--Identifier: a\n";

        CHECK_EQ(right_tree, getTree(code));
    }

    SUBCASE("Assigning double number") {
        code = "pi_numb = 3.14";
        right_tree = "PROGRAM ROOT\n"
                     "-Assign Operation\n"
                     "--DOUBLE: 3.140000\n"
                     "-is assigned to\n"
                     "--Identifier: pi_numb\n";

        CHECK_EQ(right_tree, getTree(code));
    }

    SUBCASE("Assigning negative double number") {
        code = "negative_PI = -3.14";
        right_tree = "PROGRAM ROOT\n"
                     "-Assign Operation\n"
                     "--Arithmetic NEGATION\n"
                     "---DOUBLE: 3.140000\n"
                     "-is assigned to\n"
                     "--Identifier: negative_PI\n";

        CHECK_EQ(right_tree, getTree(code));
    }

    SUBCASE("Assigning another variable") {
        code = "a = b";
        right_tree = "PROGRAM ROOT\n"
                     "-Assign Operation\n"
                     "--Identifier: b\n"
                     "-is assigned to\n"
                     "--Identifier: a\n";

        CHECK_EQ(right_tree, getTree(code));
    }

    SUBCASE("Assigning result from function call") {
        code = "a = .func(arg1, arg2)";
        right_tree = "PROGRAM ROOT\n"
                     "-Assign Operation\n"
                     "--Identifier: a\n"
                     "-is assigned to\n"
                     "--Function Call\n"
                     "---Identifier: func\n"
                     "---Function Arguments\n"
                     "----Identifier: arg1\n"
                     "----Identifier: arg2\n";

        CHECK_EQ(right_tree, getTree(code));
    }

    SUBCASE("Assigning time period") {
        code = "a = [+2:30:54]";
        right_tree = "PROGRAM ROOT\n"
                     "-Assign Operation\n"
                     "--Time period: 2 h 30 m 54 s\n"
                     "-is assigned to\n"
                     "--Identifier: a\n";

        CHECK_EQ(right_tree, getTree(code));
    }

    SUBCASE("Assigning time moment - clock") {
        code = "a = [^12:59:22]";
        right_tree = "PROGRAM ROOT\n"
                     "-Assign Operation\n"
                     "--Time moment - clock: 12:59:22\n"
                     "-is assigned to\n"
                     "--Identifier: a\n";

        CHECK_EQ(right_tree, getTree(code));
    }

    SUBCASE("Assigning time moment - date") {
        code = "a = [13/12/2021]";
        right_tree = "PROGRAM ROOT\n"
                     "-Assign Operation\n"
                     "--Time moment - date: 13/12/2021\n"
                     "-is assigned to\n"
                     "--Identifier: a\n";

        CHECK_EQ(right_tree, getTree(code));
    }

    SUBCASE("Assigning time moment - timestamp") {
        code = "a = [24/12/2021 18:15:40]";
        right_tree = "PROGRAM ROOT\n"
                     "-Assign Operation\n"
                     "--Time moment - timestamp: 24/12/2021 18:15:40\n"
                     "-is assigned to\n"
                     "--Identifier: a\n";

        CHECK_EQ(right_tree, getTree(code));
    }

    SUBCASE("Assigning expression - multiplication") {
        code = "a = [h]3 * 2";
        right_tree = "PROGRAM ROOT\n"
                     "-Assign Operation\n"
                     "--MULTIPLY operation\n"
                     "---INT: 2\n"
                     "---Convert to HOURS\n"
                     "----INT: 3\n"
                     "-is assigned to\n"
                     "--Identifier: a\n";

        CHECK_EQ(right_tree, getTree(code));
    }

    SUBCASE("Assigning expression - division") {
        code = "a = [m]60 / 2.5";
        right_tree = "PROGRAM ROOT\n"
                     "-Assign Operation\n"
                     "--DIVIDE operation\n"
                     "---DOUBLE: 2.500000\n"
                     "---Convert to MINUTES\n"
                     "----INT: 60\n"
                     "-is assigned to\n"
                     "--Identifier: a\n";

        CHECK_EQ(right_tree, getTree(code));
    }

}


TEST_SUITE_END;