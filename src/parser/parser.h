#ifndef JEZYK_Z_CZASEM_PARSER_H
#define JEZYK_Z_CZASEM_PARSER_H

#include "../lexer/lexer.h"
#include "programNode.h"

namespace parser {

    class Parser {
    public:
        Parser(lexer::Lexer &lex, ProgramNode *root) : token_source(lex), program(root) { /*parseProgram();*/ }

        void parseProgram();

    private:
        lexer::Lexer token_source;
        lexer::Token current_token;
        ProgramNode *program;

        inline void advance() { current_token = current_token.type == lexer::T_END ? current_token
                                                                                   : token_source.getNextToken();
        }

        void parseFuncDef();

        void parseInstruction(ASTNode *parent);

        void parseRet(ASTNode *parent);

        void parseIf(ASTNode *parent);

        void parseWhileLoop(ASTNode *parent);

        void parseAssignOperator(ASTNode *parent);

        void parseShowFunc(ASTNode *parent);

        void parseArithmeticExpr(ASTNode *parent);

        void parseCondition(ASTNode *parent);

        void parseInstructionsBlock(ASTNode *parent);

        void parseElif(ASTNode *parent);

        void parseElse(ASTNode *parent);

        void parseIdentifier(ASTNode *parent);

        void parseFuncArgs(ASTNode *parent);

        void parseFuncCall(ASTNode *parent);

        void parseString(ASTNode *parent);
    };
}

#endif //JEZYK_Z_CZASEM_PARSER_H
