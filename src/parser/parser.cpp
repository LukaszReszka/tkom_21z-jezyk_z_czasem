#include "parser.h"
#include "literal.h"


using std::chrono::seconds, std::chrono::minutes, std::chrono::hours;
using std::ratio, std::chrono::duration;

namespace parser {

    unique_ptr<ProgramTree> Parser::parseProgram() {
        advance();
        unique_ptr<ProgramTree> programTree = std::make_unique<ProgramTree>(context);
        while (current_token.type != lexer::T_END) {
            programTree->addCommand(std::move(parseCommand()));
            advance();
        }
        return programTree;
    }

    unique_ptr<Command> Parser::parseCommand() {
        if (current_token.type == lexer::T_FUNC)
            return std::make_unique<Command>(std::move(parseFuncDef()), context);
        else
            return std::make_unique<Command>(std::move(parseInstruction()), context);
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
            return std::make_unique<Instruction>(std::move(parseAssignOperator()));
        else if (current_token.type == lexer::T_IF)
            return std::make_unique<Instruction>(std::move(parseIf()));
        else if (current_token.type == lexer::T_WHILE)
            return std::make_unique<Instruction>(std::move(parseWhileLoop()));
        else if (current_token.type == lexer::T_DOT)
            return std::make_unique<Instruction>(std::move(parseFuncCall()));
        else if (current_token.type == lexer::T_RET)
            return std::make_unique<Instruction>(std::move(parseRet()));
        else if (current_token.type == lexer::T_SHOW)
            return std::make_unique<Instruction>(std::move(parseShowFunc()));
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

        unique_ptr<Literal> var = std::make_unique<Literal>(context);
        var->val->type = ValueType::VARIABLE;
        var->val->value_str = variable_name;

        return std::make_unique<OperatorOperation>(t, std::move(var), std::move(parseArithmeticExpr()), context);
    }

    unique_ptr<ShowFunc> Parser::parseShowFunc() {
        advance();
        if (current_token.type != lexer::T_PARENTHESES_1) {
            //TODO error "Lack of \"(\""
        }
        advance();
        vector<unique_ptr<Expression>> args;
        if (current_token.type == lexer::T_STRING) {
            unique_ptr<Literal> str = std::make_unique<Literal>(context);
            str->val->type = ValueType::STRING;
            str->val->value_str = std::get<std::string>(current_token.value);
            args.push_back(std::move(std::move(str)));
        } else
            args.push_back(std::move(parseArithmeticExpr()));

        advance();

        while (current_token.type == lexer::T_COMMA) {
            advance();
            if (current_token.type == lexer::T_STRING) {
                unique_ptr<Literal> str = std::make_unique<Literal>(context);
                str->val->type = ValueType::STRING;
                str->val->value_str = std::get<std::string>(current_token.value);
                args.push_back(std::move(std::move(str)));
            } else
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
        unique_ptr<Literal> cond = std::make_unique<Literal>(context);
        cond->val->type = ValueType::BOOL;
        cond->val->value.boolean = true;
        return std::make_unique<ElifStat>(std::move(cond), body);
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
        return std::make_unique<FuncCall>(func_name, args, context);
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
                                                       std::move(parseLogicalExpr()), context);
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

        return std::make_unique<OperatorOperation>(op_type, std::move(first_operand), std::move(parseArithmeticExpr()),
                                                   context);
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
                                                       std::move(parseArithmeticExpr()), context);
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
                                                       std::move(parseMultiplicativeExpr()), context);
        }

        return first_operand;
    }

    unique_ptr<Expression> Parser::parseFactor() {
        if (current_token.type == lexer::T_MINUS) {
            advance();
            return std::make_unique<OperatorOperation>(std::move(parseValue()), context);
        } else
            return parseValue();
    }

    unique_ptr<Expression> Parser::parseValue() {
        if (current_token.type == lexer::T_IDENTIFIER) {
            string variable_name;
            parseIdentifier(variable_name);
            unique_ptr<Literal> var = std::make_unique<Literal>(context);
            var->val->type = ValueType::VARIABLE;
            var->val->value_str = variable_name;
            return var;
        } else if (current_token.type == lexer::T_DOT) {
            return parseFuncCall();
        } else if (current_token.type == lexer::T_PARENTHESES_1) {
            advance();
            unique_ptr<Expression> arthm = std::move(parseArithmeticExpr());
            advance();
            if (current_token.type != lexer::T_PARENTHESES_2) {
                //TODO error "Lack of \")\""
            }
            return arthm;
        } else
            return std::move(parseNumericAndTimeValue());
    }

    unique_ptr<Expression> Parser::parseNumericAndTimeValue() {
        if (current_token.type == lexer::T_DATE) {
            return std::make_unique<Literal>(std::get<lexer::TimeMoment>(current_token.value), ValueType::DATE,
                                             context);
        } else if (current_token.type == lexer::T_TIMESTAMP) {
            return std::make_unique<Literal>(std::get<lexer::TimeMoment>(current_token.value), ValueType::TIMESTAMP,
                                             context);
        } else if (current_token.type == lexer::T_CLOCK) {
            return std::make_unique<Literal>(std::get<lexer::TimeMoment>(current_token.value), ValueType::CLOCK,
                                             context);
        } else if (current_token.type == lexer::T_TIME_PERIOD) {
            unique_ptr<Literal> literal = std::make_unique<Literal>(context);
            literal->val->type = ValueType::TIME_PERIOD;
            literal->val->value.int_s = (std::get<lexer::TimePeriod>(current_token.value)).getSecNumb();
            return literal;
        } else if (current_token.type == lexer::T_INT || current_token.type == lexer::T_DOUBLE) {
            return std::move(parseNumb());
        } else if (current_token.type == lexer::T_HOUR_U || current_token.type == lexer::T_MIN_U ||
                   current_token.type == lexer::T_SEC_U) {
            return std::move(parseTimeUnit());
        } //else
        //TODO error "Expected number, time moment or time period"
    }

    unique_ptr<Expression> Parser::parseTimeUnit() {
        unique_ptr<Literal> literal = std::make_unique<Literal>(context);
        if (current_token.type == lexer::T_HOUR_U) {
            advance();
            if (current_token.type == lexer::T_INT) {
                literal->val->type = ValueType::INT_H;
                literal->val->value.int_h = hours(std::get<int>(current_token.value));
                return literal;
            } else if (current_token.type == lexer::T_DOUBLE) {
                literal->val->type = ValueType::DOUBLE_H;
                literal->val->value.double_h = duration<double, ratio<3600>>(std::get<double>(current_token.value));
                return literal;
            }
        } else if (current_token.type == lexer::T_MIN_U) {
            advance();
            if (current_token.type == lexer::T_INT) {
                literal->val->type = ValueType::INT_MIN;
                literal->val->value.int_min = minutes(std::get<int>(current_token.value));
                return literal;
            } else if (current_token.type == lexer::T_DOUBLE) {
                literal->val->type = ValueType::DOUBLE_MIN;
                literal->val->value.double_min = duration<double, ratio<60>>(std::get<double>(current_token.value));
                return literal;
            }
        } else if (current_token.type == lexer::T_SEC_U) {
            advance();
            if (current_token.type == lexer::T_INT) {
                literal->val->type = ValueType::INT_S;
                literal->val->value.int_s = seconds(std::get<int>(current_token.value));
                return literal;
            } else if (current_token.type == lexer::T_DOUBLE) {
                literal->val->type = ValueType::DOUBLE_S;
                literal->val->value.double_s = duration<double>(std::get<double>(current_token.value));
                return literal;
            }
        }

        //TODO error Expected int or double
    }

    unique_ptr<Expression> Parser::parseNumb() {
        unique_ptr<Literal> literal = std::make_unique<Literal>(context);
        if (current_token.type == lexer::T_INT) {
            literal->val->type = ValueType::INT;
            literal->val->value.integer_numb = std::get<int>(current_token.value);
        } else if (current_token.type == lexer::T_DOUBLE) {
            literal->val->type = ValueType::DOUBLE;
            literal->val->value.double_numb = std::get<double>(current_token.value);
        }
        return literal;
    }
}