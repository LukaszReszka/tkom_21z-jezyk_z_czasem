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

    std::unique_ptr<Value> OperatorOperation::evaluate() {
        return std::unique_ptr<Value>();
    }
}