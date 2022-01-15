#ifndef JEZYK_Z_CZASEM_OPERATOROPERATION_H
#define JEZYK_Z_CZASEM_OPERATOROPERATION_H

#include "expression.h"

namespace parser {
    enum OperatorType {
        PLUS, MINUS, MULTIPLY, DIVIDE,                                  //arithmetic
        UNARY_MINUS,
        OR, AND,                                                        //logical
        EQUAL, NOT_EQUAL, GREATER, GREATER_EQUAL, LESS, LESS_EQUAL,     //comparison
        ASSIGN                                                          //assign
    };

    class OperatorOperation : public Expression {
    public:

        OperatorOperation(OperatorType &t, std::unique_ptr<Expression> first_op,
                          std::unique_ptr<Expression> second_op);

        explicit OperatorOperation(std::unique_ptr<Expression> op);

        std::string toString() override;

        std::unique_ptr<Value> evaluate() override;

    private:
        OperatorType type;
        std::unique_ptr<Expression> first_operand, second_operand;
    };

}

#endif //JEZYK_Z_CZASEM_OPERATOROPERATION_H
