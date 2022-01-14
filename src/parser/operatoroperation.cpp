#include "operatoroperation.h"

namespace parser {
    OperatorOperation::OperatorOperation(OperatorType &t, std::unique_ptr<Expression> first_op,
                                         std::unique_ptr<Expression> second_op) :
            type(t), first_operand(std::move(first_op)), second_operand(std::move(second_op)) {}

    OperatorOperation::OperatorOperation(std::unique_ptr<Expression> op) : type(UNARY_MINUS),
                                                                           first_operand(std::move(op)) {}

    std::string OperatorOperation::toString() {
        return std::string();
    }

    std::unique_ptr<Value> OperatorOperation::evaluate() {
        return std::unique_ptr<Value>();
    }
}