#include "parser.h"
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
            parseFuncDef();
        else
            parseInstruction(program);

        return unique_ptr<Command>();
    }

    void Parser::parseFuncDef() {
        auto *func_def = new FuncDefNode(program);
        program->children_nodes.push_back(func_def);
        advance();
        parseIdentifier(func_def);
        advance();
        parseFuncArgs(func_def);
        advance();
        parseInstructionsBlock(func_def);
    }

    void Parser::parseInstruction(ASTNode *parent) {

        if (current_token.type == lexer::T_IDENTIFIER)
            parseAssignOperator(parent);
        else if (current_token.type == lexer::T_IF)
            parseIf(parent);
        else if (current_token.type == lexer::T_WHILE)
            parseWhileLoop(parent);
        else if (current_token.type == lexer::T_DOT)
            parseFuncCall(parent);
        else if (current_token.type == lexer::T_RET)
            parseRet(parent);
        else if (current_token.type == lexer::T_SHOW)
            parseShowFunc(parent);
        else
            parent->children_nodes.push_back(new ErrorNode(parent, "Unrecognised instruction"));
    }

    void Parser::parseRet(ASTNode *parent) {
        auto *ret = new ReturnNode(parent);
        parent->children_nodes.push_back(ret);
        advance();
        if (current_token.type != lexer::T_PARENTHESES_1) {
            ret->children_nodes.push_back(new ErrorNode(ret, "Lack of \"(\""));
            return;
        }
        advance();
        parseArithmeticExpr(ret);
        advance();
        if (current_token.type != lexer::T_PARENTHESES_2) {
            ret->children_nodes.clear();
            ret->children_nodes.push_back(new ErrorNode(ret, "Lack of \")\""));
        }
    }

    void Parser::parseIf(ASTNode *parent) {
        auto *if_statement = new IfNode(parent);
        parent->children_nodes.push_back(if_statement);
        advance();
        parseCondition(if_statement);
        advance();
        parseInstructionsBlock(if_statement);
        advance();
        while (current_token.type == lexer::T_ELIF) {
            parseElif(if_statement);
            advance();
        }

        if (current_token.type == lexer::T_ELSE) {
            parseElse(if_statement);
        }
    }

    void Parser::parseWhileLoop(ASTNode *parent) {
        auto *while_loop = new WhileLoopNode(parent);
        parent->children_nodes.push_back(while_loop);
        advance();
        parseCondition(while_loop);
        advance();
        parseInstructionsBlock(while_loop);
    }

    void Parser::parseAssignOperator(ASTNode *parent) {
        auto *assign_operation = new AssignOperatorNode(parent);
        parent->children_nodes.push_back(assign_operation);
        parseIdentifier(assign_operation);
        advance();
        if (current_token.type != lexer::T_ASSIGN) {
            assign_operation->children_nodes.clear();
            assign_operation->children_nodes.push_back(
                    new ErrorNode(assign_operation, "Wrong operator - expected \"=\""));
            return;
        }
        advance();
        if (current_token.type == lexer::T_DOT)
            parseFuncCall(assign_operation);
        else
            parseArithmeticExpr(assign_operation);
    }

    void Parser::parseShowFunc(ASTNode *parent) {
        auto *show_func = new ShowFuncNode(parent);
        parent->children_nodes.push_back(show_func);
        advance();

        if (current_token.type != lexer::T_PARENTHESES_1) {
            show_func->children_nodes.push_back(new ErrorNode(show_func, "Lack of \"(\""));
            return;
        }
        advance();
        if (current_token.type == lexer::T_STRING)
            parseString(show_func);
        else
            parseArithmeticExpr(show_func);
        advance();

        while (current_token.type == lexer::T_COMMA) {
            advance();
            if (current_token.type == lexer::T_STRING)
                parseString(show_func);
            else
                parseArithmeticExpr(show_func);
            advance();
        }

        if (current_token.type != lexer::T_PARENTHESES_2) {
            show_func->children_nodes.clear();
            show_func->children_nodes.push_back(new ErrorNode(show_func, "Lack of \")\""));
        }
    }

    void Parser::parseInstructionsBlock(ASTNode *parent) {
        auto *block = new BlockNode(parent);
        parent->children_nodes.push_back(block);
        if (current_token.type != lexer::T_BRACE_1) {
            block->children_nodes.push_back(new ErrorNode(block, "Lack of \"{\""));
            return;
        }
        advance();
        while (current_token.type != lexer::T_END && current_token.type != lexer::T_BRACE_2) {
            parseInstruction(block);
            advance();
        }

        if (current_token.type != lexer::T_BRACE_2) {
            block->children_nodes.clear();
            block->children_nodes.push_back(new ErrorNode(block, "Lack of \"}\""));
            return;
        }
    }

    void Parser::parseElif(ASTNode *parent) {
        auto *elif_statement = new ElifNode(parent);
        parent->children_nodes.push_back(elif_statement);
        advance();
        parseCondition(elif_statement);
        advance();
        parseInstructionsBlock(elif_statement);
    }

    void Parser::parseElse(ASTNode *parent) {
        auto *else_statement = new ElseNode(parent);
        parent->children_nodes.push_back(else_statement);
        advance();
        parseInstructionsBlock(else_statement);
    }

    void Parser::parseIdentifier(ASTNode *parent) {
        if (current_token.type == lexer::T_IDENTIFIER) {
            auto *id = new IdentifierNode(parent);
            id->identifier = std::get<std::string>(current_token.value);
            parent->children_nodes.push_back(id);
        } else
            parent->children_nodes.push_back(new ErrorNode(parent, "Expected identifier"));
    }

    void Parser::parseFuncArgs(ASTNode *parent) {
        auto *func_args = new FuncArgsNode(parent);
        parent->children_nodes.push_back(func_args);

        if (current_token.type != lexer::T_PARENTHESES_1) {
            func_args->children_nodes.push_back(new ErrorNode(func_args, "Lack of \"(\""));
            return;
        }
        advance();

        if (current_token.type == lexer::T_IDENTIFIER) {
            parseIdentifier(func_args);
            advance();
            while (current_token.type == lexer::T_COMMA) {
                advance();
                parseIdentifier(func_args);
                advance();
            }
        }

        if (current_token.type != lexer::T_PARENTHESES_2) {
            func_args->children_nodes.clear();
            func_args->children_nodes.push_back(new ErrorNode(func_args, "Lack of \")\""));
        }
    }

    void Parser::parseFuncCall(ASTNode *parent) {
        auto *func_call = new FuncCallNode(parent);
        parent->children_nodes.push_back(func_call);
        advance();
        parseIdentifier(func_call);
        advance();
        parseFuncArgs(func_call);
    }

    void Parser::parseString(ASTNode *parent) {
        auto *string_node = new StringNode(parent);
        parent->children_nodes.push_back(string_node);
        string_node->str = std::get<std::string>(current_token.value);
    }

    void Parser::parseCondition(ASTNode *parent) {
        auto *condition = new ConditionNode(parent);
        parent->children_nodes.push_back(condition);

        if (current_token.type != lexer::T_PARENTHESES_1) {
            condition->children_nodes.push_back(new ErrorNode(condition, "Lack of \"(\""));
            return;
        }

        advance();
        parseLogicalExpr(condition);
        advance();

        if (current_token.type != lexer::T_PARENTHESES_2) {
            condition->children_nodes.clear();
            condition->children_nodes.push_back(new ErrorNode(condition, "Lack of \")\""));
        }
    }

    void Parser::parseLogicalExpr(ASTNode *parent) {
        auto *binary_operation = new BinaryOperatorsNode(parent);
        parent->children_nodes.push_back(binary_operation);
        parseComparisonExpr(binary_operation);
        advance();
        if (current_token.type == lexer::T_OR || current_token.type == lexer::T_AND) {
            if (current_token.type == lexer::T_OR)
                binary_operation->operator_type = OR;
            else if (current_token.type == lexer::T_AND)
                binary_operation->operator_type = AND;
            advance();
            parseLogicalExpr(binary_operation);
        } else {
            parent->children_nodes.insert(parent->children_nodes.begin(), binary_operation->children_nodes[0]);
            parent->children_nodes[0]->parent_node = parent;
            binary_operation->children_nodes[0] = nullptr;
            binary_operation->children_nodes.clear();
            parent->children_nodes.pop_back();
        }
    }

    void Parser::parseComparisonExpr(ASTNode *parent) {
        auto *binary_operation = new BinaryOperatorsNode(parent);
        parent->children_nodes.push_back(binary_operation);
        parseArithmeticExpr(binary_operation);
        advance();
        if (current_token.type == lexer::T_EQUAL)
            binary_operation->operator_type = EQUAL;
        else if (current_token.type == lexer::T_NOT_EQUAL)
            binary_operation->operator_type = NOT_EQUAL;
        else if (current_token.type == lexer::T_GREATER)
            binary_operation->operator_type = GREATER;
        else if (current_token.type == lexer::T_GREATER_E)
            binary_operation->operator_type = GREATER_EQUAL;
        else if (current_token.type == lexer::T_LESS)
            binary_operation->operator_type = LESS;
        else if (current_token.type == lexer::T_LESS_E)
            binary_operation->operator_type = LESS_EQUAL;
        else {
            binary_operation->children_nodes.clear();
            binary_operation->children_nodes.push_back(
                    new ErrorNode(binary_operation, "Wrong operator - expected comparison operator"));
            return;
        }
        advance();
        parseArithmeticExpr(binary_operation);
    }

    void Parser::parseArithmeticExpr(ASTNode *parent) {
        auto *binary_operation = new BinaryOperatorsNode(parent);
        parent->children_nodes.push_back(binary_operation);
        parseMultiplicativeExpr(binary_operation);
        advance();
        if (current_token.type == lexer::T_PLUS || current_token.type == lexer::T_MINUS) {
            if (current_token.type == lexer::T_PLUS)
                binary_operation->operator_type = PLUS;
            else if (current_token.type == lexer::T_MINUS)
                binary_operation->operator_type = MINUS;
            advance();
            parseArithmeticExpr(binary_operation);
        } else {
            parent->children_nodes.insert(parent->children_nodes.begin(), binary_operation->children_nodes[0]);
            parent->children_nodes[0]->parent_node = parent;
            binary_operation->children_nodes[0] = nullptr;
            binary_operation->children_nodes.clear();
            parent->children_nodes.pop_back();
        }
    }

    void Parser::parseMultiplicativeExpr(ASTNode *parent) {
        auto *binary_operation = new BinaryOperatorsNode(parent);
        parent->children_nodes.push_back(binary_operation);
        parseFactor(binary_operation);
        advance();
        if (current_token.type == lexer::T_MULTIPLY || current_token.type == lexer::T_DIVIDE) {
            if (current_token.type == lexer::T_MULTIPLY)
                binary_operation->operator_type = MULTIPLY;
            else if (current_token.type == lexer::T_DIVIDE)
                binary_operation->operator_type = DIVIDE;
            advance();
            parseMultiplicativeExpr(binary_operation);
        } else {
            parent->children_nodes.insert(parent->children_nodes.begin(), binary_operation->children_nodes[0]);
            parent->children_nodes[0]->parent_node = parent;
            binary_operation->children_nodes[0] = nullptr;
            binary_operation->children_nodes.clear();
            parent->children_nodes.pop_back();
        }
    }

    void Parser::parseFactor(ASTNode *parent) {
        if (current_token.type == lexer::T_MINUS) {
            auto *unary_minus = new UnaryOperatorNode(parent);
            parent->children_nodes.push_back(unary_minus);
            advance();
            parseValue(unary_minus);
        } else
            parseValue(parent);
    }

    void Parser::parseValue(ASTNode *parent) {
        if (current_token.type == lexer::T_IDENTIFIER)
            parseIdentifier(parent);
        else if (current_token.type == lexer::T_DOT)
            parseFuncCall(parent);
        else if (current_token.type == lexer::T_PARENTHESES_1) {
            advance();
            parseArithmeticExpr(parent);
            advance();
            if (current_token.type != lexer::T_PARENTHESES_2) {
                parent->children_nodes.clear();
                parent->children_nodes.push_back(new ErrorNode(parent, "Lack of \")\""));
                return;
            }
        } else
            parseNumericAndTimeValue(parent);
    }

    void Parser::parseNumericAndTimeValue(ASTNode *parent) {
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
        } else
            parent->children_nodes.push_back(new ErrorNode(parent, "Expected number, time moment or time period"));
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