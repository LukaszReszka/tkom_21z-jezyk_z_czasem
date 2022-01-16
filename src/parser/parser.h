#ifndef JEZYK_Z_CZASEM_PARSER_H
#define JEZYK_Z_CZASEM_PARSER_H

#include "../lexer/lexer.h"
#include "../interpreter/context.h"
#include "programtree.h"
#include "ifstatement.h"
#include "operatoroperation.h"
#include <memory>
#include <utility>

using std::unique_ptr, std::shared_ptr;
using std::string;
using std::vector;

namespace parser {

    class Parser {
    public:
        explicit Parser(lexer::Lexer &lex, shared_ptr<interpreter::Context> c) : token_source(lex),
                                                                                 context(std::move(c)) {}

        unique_ptr<ProgramTree> parseProgram();

    private:
        lexer::Lexer token_source;
        lexer::Token current_token;
        shared_ptr<interpreter::Context> context;

        inline void advance() {
            current_token = current_token.type == lexer::T_END ? current_token
                                                               : token_source.getNextToken();
        }

        unique_ptr<Command> parseCommand();

        unique_ptr<FuncDef> parseFuncDef();

        unique_ptr<Instruction> parseInstruction();

        unique_ptr<ReturnInstr> parseRet();

        unique_ptr<IfStatement> parseIf();

        unique_ptr<WhileLoop> parseWhileLoop();

        unique_ptr<OperatorOperation> parseAssignOperator();

        unique_ptr<ShowFunc> parseShowFunc();

        unique_ptr<Expression> parseArithmeticExpr();

        unique_ptr<Expression> parseCondition();

        void parseInstructionsBlock(vector<unique_ptr<Phrase>> &instructs);

        unique_ptr<ElifStat> parseElif();

        unique_ptr<ElifStat> parseElse();

        void parseIdentifier(string &ident);

        void parseFuncArgs(vector<string> &args);

        unique_ptr<FuncCall> parseFuncCall();

        unique_ptr<Expression> parseLogicalExpr();

        unique_ptr<Expression> parseComparisonExpr();

        unique_ptr<Expression> parseMultiplicativeExpr();

        unique_ptr<Expression> parseFactor();

        unique_ptr<Expression> parseValue();

        unique_ptr<Expression> parseNumericAndTimeValue();

        unique_ptr<Expression> parseTimeUnit();

        unique_ptr<Expression> parseNumb();
    };
}

#endif //JEZYK_Z_CZASEM_PARSER_H
