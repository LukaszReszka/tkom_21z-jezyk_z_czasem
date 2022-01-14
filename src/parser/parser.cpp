#include "parser.h"

#include <memory>
#include "returnNode.h"
#include "whileLoopNode.h"
#include "blockNode.h"
#include "ifNode.h"
#include "errorNode.h"
#include "elifNode.h"
#include "elseNode.h"
#include "funcDefNode.h"
#include "identifierNode.h"
#include "funcArgsNode.h"
#include "funcCallNode.h"
#include "assignOperatorNode.h"
#include "showFuncNode.h"
#include "stringNode.h"
#include "conditionNode.h"
#include "binaryOperatorsNode.h"
#include "unaryOperatorNode.h"
#include "timePeriodNode.h"
#include "dateNode.h"
#include "timestampNode.h"
#include "clockNode.h"
#include "intNode.h"
#include "doubleNode.h"
#include "returninstr.h"
#include "operatoroperation.h"
#include "literal.h"
#include "whileloop.h"

namespace parser {

    unique_ptr<ProgramTree> Parser::parseProgram() {
        advance();
        unique_ptr<ProgramTree> programTree(new ProgramTree());
        while (current_token.type != lexer::T_END) {
            programTree->addCommand(parseCommand());
            advance();
        }
        return programTree;
    }

    unique_ptr<Command> Parser::parseCommand() {
        if (current_token.type == lexer::T_FUNC)
            return std::make_unique<Command>(parseFuncDef());
        else
            return std::make_unique<Command>(parseInstruction());
    }

    unique_ptr<FuncDef> Parser::parseFuncDef() {
        advance();
        string func_name;
        parseIdentifier(func_name);
        advance();
        vector<string> func_args;
        parseFuncArgs(func_args);
        advance();
        vector<unique_ptr<Phrase>> body;
        parseInstructionsBlock(body);
        return std::make_unique<FuncDef>(func_name, func_args, body);
    }

    unique_ptr<Instruction> Parser::parseInstruction() {

        if (current_token.type == lexer::T_IDENTIFIER)
            return std::make_unique<Instruction>(parseAssignOperator());
        else if (current_token.type == lexer::T_IF)
            return std::make_unique<Instruction>(parseIf());
        else if (current_token.type == lexer::T_WHILE)
            return std::make_unique<Instruction>(parseWhileLoop());
        else if (current_token.type == lexer::T_DOT)
            return std::make_unique<Instruction>(parseFuncCall());
        else if (current_token.type == lexer::T_RET)
            return std::make_unique<Instruction>(parseRet());
        else if (current_token.type == lexer::T_SHOW)
            return std::make_unique<Instruction>(parseShowFunc());
        //else
        //TODO error "Unrecognised instruction"
    }

    unique_ptr<ReturnInstr> Parser::parseRet() {
        advance();
        if (current_token.type != lexer::T_PARENTHESES_1) {
            //TODO error "Lack of \"(\""
        }

        advance();
        unique_ptr<Expression> ret_val = std::move(parseArithmeticExpr());
        advance();

        if (current_token.type != lexer::T_PARENTHESES_2) {
            //TODO error "Lack of \")\""
        }
        return std::make_unique<ReturnInstr>(std::move(ret_val));
    }

    unique_ptr<IfStatement> Parser::parseIf() {
        advance();
        unique_ptr<Expression> cond = std::move(parseCondition());
        advance();
        vector<unique_ptr<Phrase>> body;
        parseInstructionsBlock(body);
        advance();
        vector<unique_ptr<ElifStat>> elifs;
        while (current_token.type == lexer::T_ELIF) {
            elifs.push_back(std::move(parseElif()));
            advance();
        }

        if (current_token.type == lexer::T_ELSE) {
            elifs.push_back(std::move(parseElse()));
        }

        return std::make_unique<IfStatement>(std::move(cond), body, elifs);
    }

    unique_ptr<WhileLoop> Parser::parseWhileLoop() {
        advance();
        unique_ptr<Expression> cond = std::move(parseCondition());
        advance();
        vector<unique_ptr<Phrase>> body;
        parseInstructionsBlock(body);
        return std::make_unique<WhileLoop>(std::move(cond), body);
    }

    unique_ptr<OperatorOperation> Parser::parseAssignOperator() {
        string variable_name;
        parseIdentifier(variable_name);
        advance();

        if (current_token.type != lexer::T_ASSIGN) {
            //TODO error "Wrong operator - expected \"=\""
        }
        OperatorType t = OperatorType::ASSIGN;
        advance();

        return std::make_unique<OperatorOperation>(t, std::move(std::make_unique<Literal>(variable_name)),
                                                   std::move(parseArithmeticExpr()));
    }

    unique_ptr<ShowFunc> Parser::parseShowFunc() {
        advance();
        if (current_token.type != lexer::T_PARENTHESES_1) {
            //TODO error "Lack of \"(\""
        }
        advance();
        vector<unique_ptr<Expression>> args;
        if (current_token.type == lexer::T_STRING)
            args.push_back(std::move(std::make_unique<Literal>(std::get<std::string>(current_token.value),
                                                               ValueType::STRING)));
        else
            args.push_back(std::move(parseArithmeticExpr()));

        advance();

        while (current_token.type == lexer::T_COMMA) {
            advance();
            if (current_token.type == lexer::T_STRING)
                args.push_back(std::move(std::make_unique<Literal>(std::get<std::string>(current_token.value),
                                                                   ValueType::STRING)));
            else
                args.push_back(std::move(parseArithmeticExpr()));
            advance();
        }

        if (current_token.type != lexer::T_PARENTHESES_2) {
            //TODO error "Lack of \")\""
        }

        return std::make_unique<ShowFunc>(args);
    }

    void Parser::parseInstructionsBlock(vector<unique_ptr<Phrase>> &instructs) {
        if (current_token.type != lexer::T_BRACE_1) {
            //TODO error "Lack of \"{\""
        }
        advance();

        while (current_token.type != lexer::T_END && current_token.type != lexer::T_BRACE_2) {
            instructs.push_back(std::move(parseInstruction()));
            advance();
        }

        if (current_token.type != lexer::T_BRACE_2) {
            //TODO error "Lack of \"}\""
        }
    }

    unique_ptr<ElifStat> Parser::parseElif() {
        advance();
        unique_ptr<Expression> cond = std::move(parseCondition());
        advance();
        vector<unique_ptr<Phrase>> body;
        parseInstructionsBlock(body);
        return std::make_unique<ElifStat>(std::move(cond), body);
    }

    unique_ptr<ElifStat> Parser::parseElse() {
        advance();
        vector<unique_ptr<Phrase>> body;
        parseInstructionsBlock(body);
        return std::make_unique<ElifStat>(std::move(std::make_unique<Literal>(true)), body);
    }

    void Parser::parseIdentifier(string &ident) {
        ident.clear();
        if (current_token.type == lexer::T_IDENTIFIER) {
            ident = std::get<std::string>(current_token.value);
        }
        //else
        //TODO error "Expected identifier"
    }

    void Parser::parseFuncArgs(vector<string> &args) {
        args.clear();
        if (current_token.type != lexer::T_PARENTHESES_1) {
            //TODO error "Lack of \"(\""
        }
        advance();

        if (current_token.type == lexer::T_IDENTIFIER) {
            string ident;
            parseIdentifier(ident);
            args.push_back(ident);
            advance();
            while (current_token.type == lexer::T_COMMA) {
                advance();
                parseIdentifier(ident);
                args.push_back(ident);
                advance();
            }
        }

        if (current_token.type != lexer::T_PARENTHESES_2) {
            //TODO error "Lack of \")\""
        }
    }

    unique_ptr<FuncCall> Parser::parseFuncCall() {  //TODO jako argumenty tylko zmienne, bez wyrażeń ...
        advance();
        string func_name;
        parseIdentifier(func_name);
        advance();
        vector<string> args;
        parseFuncArgs(args);
        return std::make_unique<FuncCall>(func_name, args);
    }

    unique_ptr<Expression> Parser::parseCondition() {
        if (current_token.type != lexer::T_PARENTHESES_1) {
            //TODO error "Lack of \"(\""
        }

        advance();
        unique_ptr<Expression> cond = std::move(parseLogicalExpr());
        advance();

        if (current_token.type != lexer::T_PARENTHESES_2) {
            //TODO error "Lack of \")\""
        }

        return cond;
    }

    unique_ptr<Expression> Parser::parseLogicalExpr() {
        unique_ptr<Expression> first_operand = std::move(parseComparisonExpr());
        advance();
        if (current_token.type == lexer::T_OR || current_token.type == lexer::T_AND) {
            OperatorType op_type;
            if (current_token.type == lexer::T_OR)
                op_type = OperatorType::OR;
            else if (current_token.type == lexer::T_AND)
                op_type = OperatorType::AND;
            advance();
            return std::make_unique<OperatorOperation>(op_type, std::move(first_operand),
                                                       std::move(parseLogicalExpr()));
        }

        return first_operand;
    }

    unique_ptr<Expression> Parser::parseComparisonExpr() {
        unique_ptr<Expression> first_operand = std::move(parseArithmeticExpr());
        advance();
        OperatorType op_type;
        if (current_token.type == lexer::T_EQUAL)
            op_type = OperatorType::EQUAL;
        else if (current_token.type == lexer::T_NOT_EQUAL)
            op_type = OperatorType::NOT_EQUAL;
        else if (current_token.type == lexer::T_GREATER)
            op_type = OperatorType::GREATER;
        else if (current_token.type == lexer::T_GREATER_E)
            op_type = OperatorType::GREATER_EQUAL;
        else if (current_token.type == lexer::T_LESS)
            op_type = OperatorType::LESS;
        else if (current_token.type == lexer::T_LESS_E)
            op_type = OperatorType::LESS_EQUAL;
        else {
            //TODO error "Wrong operator - expected comparison operator"
        }
        advance();

        return std::make_unique<OperatorOperation>(op_type, std::move(first_operand), std::move(parseArithmeticExpr()));
    }

    unique_ptr<Expression> Parser::parseArithmeticExpr() {
        unique_ptr<Expression> first_operand = std::move(parseMultiplicativeExpr());
        advance();

        if (current_token.type == lexer::T_PLUS || current_token.type == lexer::T_MINUS) {

            OperatorType op_type;
            if (current_token.type == lexer::T_PLUS)
                op_type = OperatorType::PLUS;
            else if (current_token.type == lexer::T_MINUS)
                op_type = OperatorType::MINUS;
            advance();
            return std::make_unique<OperatorOperation>(op_type, std::move(first_operand),
                                                       std::move(parseArithmeticExpr()));
        }

        return first_operand;
    }

    unique_ptr<Expression> Parser::parseMultiplicativeExpr() {
        unique_ptr<Expression> first_operand = std::move(parseFactor());
        advance();

        if (current_token.type == lexer::T_MULTIPLY || current_token.type == lexer::T_DIVIDE) {
            OperatorType op_type;
            if (current_token.type == lexer::T_MULTIPLY)
                op_type = OperatorType::MULTIPLY;
            else if (current_token.type == lexer::T_DIVIDE)
                op_type = OperatorType::DIVIDE;
            advance();
            return std::make_unique<OperatorOperation>(op_type, std::move(first_operand),
                                                       std::move(parseMultiplicativeExpr()));
        }

        return first_operand;
    }

    unique_ptr<Expression> Parser::parseFactor() {
        if (current_token.type == lexer::T_MINUS)
            return std::make_unique<OperatorOperation>(std::move(parseValue()));
        else
            return parseValue();
    }

    unique_ptr<Expression> Parser::parseValue() {
        if (current_token.type == lexer::T_IDENTIFIER) {
            string variable_name;
            parseIdentifier(variable_name);
            return std::make_unique<Literal>(variable_name);
        } else if (current_token.type == lexer::T_DOT)
            return parseFuncCall();
        else if (current_token.type == lexer::T_PARENTHESES_1) {
            advance();
            return parseArithmeticExpr();
            advance();
            if (current_token.type != lexer::T_PARENTHESES_2) {
                //TODO error "Lack of \")\""
            }
        } else
            return parseNumericAndTimeValue();
    }

    unique_ptr<Expression> Parser::parseNumericAndTimeValue() {
        if (current_token.type == lexer::T_DATE) {
            auto *date = new DateNode(parent);
            date->moment = std::get<lexer::TimeMoment>(current_token.value);
            parent->children_nodes.push_back(date);
        } else if (current_token.type == lexer::T_TIMESTAMP) {
            auto *timestamp = new TimestampNode(parent);
            timestamp->moment = std::get<lexer::TimeMoment>(current_token.value);
            parent->children_nodes.push_back(timestamp);
        } else if (current_token.type == lexer::T_CLOCK) {
            auto *clock = new ClockNode(parent);
            clock->moment = std::get<lexer::TimeMoment>(current_token.value);
            parent->children_nodes.push_back(clock);
        } else if (current_token.type == lexer::T_TIME_PERIOD) {
            auto *time_period = new TimePeriodNode(parent);
            time_period->period = std::get<lexer::TimePeriod>(current_token.value);
            parent->children_nodes.push_back(time_period);
        } else if (current_token.type == lexer::T_INT || current_token.type == lexer::T_DOUBLE) {
            parseNumbers(parent);
        } else if (current_token.type == lexer::T_HOUR_U || current_token.type == lexer::T_MIN_U ||
                   current_token.type == lexer::T_SEC_U) {
            parseTimeUnit(parent);
        } //else
        //TODO error "Expected number, time moment or time period"
    }

    void Parser::parseNumbers(ASTNode *parent) {
        if (current_token.type == lexer::T_INT) {
            auto *number = new IntNode(parent);
            number->value = std::get<int>(current_token.value);
            parent->children_nodes.push_back(number);
        } else if (current_token.type == lexer::T_DOUBLE) {
            auto *number = new DoubleNode(parent);
            number->value = std::get<double>(current_token.value);
            parent->children_nodes.push_back(number);
        } else
            parent->children_nodes.push_back(new ErrorNode(parent, "Expected number"));
    }


    void Parser::parseTimeUnit(ASTNode *parent) {
        auto *time_operator = new UnaryOperatorNode(parent);
        parent->children_nodes.push_back(time_operator);

        if (current_token.type == lexer::T_HOUR_U) {
            time_operator->operator_type = HOUR;
        } else if (current_token.type == lexer::T_MIN_U) {
            time_operator->operator_type = MIN;
        } else if (current_token.type == lexer::T_SEC_U) {
            time_operator->operator_type = SEC;
        }

        advance();
        parseNumbers(time_operator);
    }
}