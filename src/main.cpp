/* TKOM21Z - Język z czasem
 * Autor: Łukasz Reszka (300257)
 * */

#include <iostream>
#include "codeSource.h"
#include "lexer.h"

int main(int argc, char **argv) {
    CodeSource *source;

    if (argc == 2) {            //source code from file

        std::string launch_arg = std::string(argv[1]);

        if (launch_arg.size() < 5 || launch_arg.substr(launch_arg.size() - 4, 4) != ".txt") {
            std::cerr << "\033[31mInvalid argument - input name of TXT file with source code (for example: code.txt)"
                      << std::endl;
            return -1;
        }
        try {
            source = new CodeSource(launch_arg);
        } catch (...) {
            std::cerr << "\033[31mError - file not found!" << std::endl;
            return -1;
        }

    } else if (argc == 1) {     //source code from console
        source = new CodeSource(std::cin);
    } else {
        std::cerr << "\033[31mToo many arguments - at the most one argument allowed!" << std::endl;
        return -1;
    }

    Lexer lexer(source);

    //***********************************************************************
    //Ta część jest tylko do testów - później będzie usunięta

    std::map<int, std::string> token_names;
    token_names[0] = "T_FUNC";
    token_names[1] = "T_IF";
    token_names[2] = "T_ELSE";
    token_names[3] = "T_WHILE";
    token_names[4] = "T_RET";
    token_names[5] = "T_IDENTIFIER";
    token_names[6] = "T_STRING";
    token_names[7] = "T_INT";
    token_names[8] = "T_DOUBLE";
    token_names[9] = "T_SEC_U";
    token_names[10] = "T_MIN_U";
    token_names[11] = "T_HOUR_U";
    token_names[12] = "T_DAY_U";
    token_names[13] = "T_DATE";
    token_names[14] = "T_TIMESTAMP";
    token_names[15] = "T_CLOCK";
    token_names[16] = "T_TIME_PERIOD";
    token_names[17] = "T_ASSIGN";
    token_names[18] = "T_PLUS";
    token_names[19] = "T_MINUS";
    token_names[20] = "T_MULTIPLY";
    token_names[21] = "T_DIVIDE";
    token_names[22] = "T_OR";
    token_names[23] = "T_AND";
    token_names[24] = "T_EQUAL";
    token_names[25] = "T_NOT_EQUAL";
    token_names[26] = "T_GREATER";
    token_names[27] = "T_GREATER_E";
    token_names[28] = "T_LESSER";
    token_names[28] = "T_LESSER_E";
    token_names[30] = "T_SEMICOLON";
    token_names[31] = "T_COMMA";
    token_names[32] = "T_PARENTHESES_1";
    token_names[33] = "T_PARENTHESES_2";
    token_names[34] = "T_BRACE_1";
    token_names[35] = "T_BRACE_2";
    token_names[36] = "T_END";
    token_names[37] = "T_UNKNOWN";

    Token t;
    std::cout << "\nRozpoznane tokeny:\n";

    do {
        lexer.getNextToken(&t);
        std::cout << token_names[t.type] << std::endl;
    } while (t.type != T_END);

    //***********************************************************************

    return 0;
}
