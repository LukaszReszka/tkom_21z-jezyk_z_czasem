/* TKOM21Z - Język z czasem
 * Autor: Łukasz Reszka (300257)
 * */

#include <iostream>
#include "codeSource/codeSource.h"
#include "lexer/lexer.h"
#include "parser/parser.h"

int main() {
    code_source::CodeSource source(std::cin);
    lexer::Lexer lexer(source);
    parser::ProgramNode *program = new parser::ProgramNode();
    parser::Parser parser(lexer, program);

    //***********************************************************************
    //Ta część jest tylko do testów - później będzie usunięta

    std::map<int, std::string> token_names;
    token_names[0] = "T_FUNC";
    token_names[1] = "T_IF";
    token_names[2] = "T_ELIF";
    token_names[3] = "T_ELSE";
    token_names[4] = "T_WHILE";
    token_names[5] = "T_RET";
    token_names[6] = "T_IDENTIFIER";
    token_names[7] = "T_STRING";
    token_names[8] = "T_INT";
    token_names[9] = "T_DOUBLE";
    token_names[10] = "T_SEC_U";
    token_names[11] = "T_MIN_U";
    token_names[12] = "T_HOUR_U";
    token_names[13] = "T_SHOW";
    token_names[14] = "T_DATE";
    token_names[15] = "T_TIMESTAMP";
    token_names[16] = "T_CLOCK";
    token_names[17] = "T_TIME_PERIOD";
    token_names[18] = "T_ASSIGN";
    token_names[19] = "T_PLUS";
    token_names[20] = "T_MINUS";
    token_names[21] = "T_MULTIPLY";
    token_names[22] = "T_DIVIDE";
    token_names[23] = "T_OR";
    token_names[24] = "T_AND";
    token_names[25] = "T_EQUAL";
    token_names[26] = "T_NOT_EQUAL";
    token_names[27] = "T_GREATER";
    token_names[28] = "T_GREATER_E";
    token_names[29] = "T_LESS";
    token_names[30] = "T_LESS_E";
    token_names[31] = "T_DOT";
    token_names[32] = "T_COMMA";
    token_names[33] = "T_PARENTHESES_1";
    token_names[34] = "T_PARENTHESES_2";
    token_names[35] = "T_BRACE_1";
    token_names[36] = "T_BRACE_2";
    token_names[37] = "T_END";
    token_names[38] = "T_NUMBER_TO_LARGE";
    token_names[39] = "T_UNKNOWN";

    std::cout << "\nRozpoznane tokeny:\n";

    lexer::Token t = lexer.getNextToken();
    while (t.type != lexer::T_END) {
        std::cout << token_names[t.type] << " : ";
        if (std::holds_alternative<int>(t.value))
            std::cout << std::get<int>(t.value) << std::endl;
        else if (std::holds_alternative<double>(t.value))
            std::cout << std::get<double>(t.value) << std::endl;
        else if (std::holds_alternative<std::string>(t.value))
            std::cout << std::get<std::string>(t.value) << std::endl;
        t = lexer.getNextToken();
    }

    //***********************************************************************

    return 0;
}
