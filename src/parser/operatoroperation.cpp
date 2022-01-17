#include <memory>
#include <utility>
#include "operatoroperation.h"

namespace parser {
    OperatorOperation::OperatorOperation(OperatorType &t, std::unique_ptr<Expression> first_op,
                                         std::unique_ptr<Expression> second_op, std::shared_ptr<interpreter::Context> c)
            : type(t), first_operand(std::move(first_op)), second_operand(std::move(second_op)),
              context(std::move(c)) {}

    OperatorOperation::OperatorOperation(std::unique_ptr<Expression> op, std::shared_ptr<interpreter::Context> c)
            : type(UNARY_MINUS), first_operand(std::move(op)), context(std::move(c)) {}

    std::string OperatorOperation::toString(int depth) {
        std::string hyphens;
        for (int i = 0; i < depth; ++i)
            hyphens += "-";
        std::string text_rep = hyphens + "Operator ";
        hyphens += "-";
        if (type == OperatorType::PLUS)
            text_rep += "PLUS";
        else if (type == OperatorType::MINUS)
            text_rep += "MINUS";
        else if (type == OperatorType::MULTIPLY)
            text_rep += "MULTIPLY";
        else if (type == OperatorType::DIVIDE)
            text_rep += "DIVIDE";
        else if (type == OperatorType::UNARY_MINUS)
            text_rep += "UNARY_MINUS";
        else if (type == OperatorType::OR)
            text_rep += "OR";
        else if (type == OperatorType::AND)
            text_rep += "AND";
        else if (type == OperatorType::EQUAL)
            text_rep += "EQUAL";
        else if (type == OperatorType::NOT_EQUAL)
            text_rep += "NOT_EQUAL";
        else if (type == OperatorType::GREATER)
            text_rep += "GREATER";
        else if (type == OperatorType::GREATER_EQUAL)
            text_rep += "GREATER_EQUAL";
        else if (type == OperatorType::LESS)
            text_rep += "LESS";
        else if (type == OperatorType::LESS_EQUAL)
            text_rep += "LESS_EQUAL";
        else if (type == OperatorType::ASSIGN)
            text_rep += "ASSIGN";

        text_rep += "\n" + hyphens + "First Operand:\n" + first_operand->toString(depth + 2);
        if (type != OperatorType::UNARY_MINUS)
            text_rep += hyphens + "Second Operand:\n" + second_operand->toString(depth + 2);

        return text_rep;
    }

    std::shared_ptr<Value> OperatorOperation::evaluate() {
        std::shared_ptr<Value> left_value = first_operand->evaluate();
        std::shared_ptr<Value> right_value;
        if (type != UNARY_MINUS)
            right_value = second_operand->evaluate();

        if (type == ASSIGN) {
            assign(right_value, left_value);
        } else if (type == PLUS)
            return addition(left_value, right_value);
        //else if (type == MINUS)
        //    return subtraction(left_value, right_value);
        //else if (type == MULTIPLY)
        //    return multiplication(left_value, right_value);
        //else
        // ...

        return {};
    }

    std::shared_ptr<Value> OperatorOperation::addition(std::shared_ptr<Value> val1, std::shared_ptr<Value> val2) {
        std::shared_ptr<Value> returned_val;
        if (val1->type == ValueType::INT && val2->type == ValueType::INT) {
            returned_val->type = ValueType::INT;
            returned_val->value.integer_numb = val1->value.integer_numb + val2->value.integer_numb;
        } else if (val1->type == ValueType::INT_H && val2->type == ValueType::INT_H) {
            returned_val->type = ValueType::INT_H;
            returned_val->value.int_h = val1->value.int_h + val2->value.int_h;
        }
            //else if ...
        else
            throw std::runtime_error("Cannot use addition with specified operands\n");
        return returned_val;
    }

    void OperatorOperation::assign(const std::shared_ptr<Value> &val1, std::shared_ptr<Value> val2) {
        if (val1->type != ValueType::VARIABLE)
            throw std::runtime_error("Cannot assign value to non-variable\n");

        context->addVariable(val1->value_str, std::move(val2));
    }

}