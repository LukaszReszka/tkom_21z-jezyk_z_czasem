#ifndef JEZYK_Z_CZASEM_PARSER_H
#define JEZYK_Z_CZASEM_PARSER_H

#include "../lexer/lexer.h"
#include "programNode.h"
#include "programtree.h"
#include "command.h"
#include <memory>

using std::unique_ptr;

namespace parser {

    class Parser {
    public:
        Parser(lexer::Lexer &lex, ProgramNode *root) : token_source(lex), program(root) {}  //TODO delete program(root)

        unique_ptr<ProgramTree> parseProgram();

    private:
        lexer::Lexer token_source;
        lexer::Token current_token;
        ProgramNode *program;  //TODO delete

        inline void advance() {
            current_token = current_token.type == lexer::T_END ? current_token
                                                               : token_source.getNextToken();
        }

        unique_ptr<Command> parseCommand();

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

        void parseLogicalExpr(ASTNode *parent);

        void parseComparisonExpr(ASTNode *parent);

        void parseMultiplicativeExpr(ASTNode *parent);

        void parseFactor(ASTNode *parent);

        void parseValue(ASTNode *parent);

        void parseNumericAndTimeValue(ASTNode *parent);

        void parseTimeUnit(ASTNode *parent);

        void parseNumbers(ASTNode *parent);
    };
}

#endif //JEZYK_Z_CZASEM_PARSER_H
