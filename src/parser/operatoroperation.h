#ifndef JEZYK_Z_CZASEM_OPERATOROPERATION_H
#define JEZYK_Z_CZASEM_OPERATOROPERATION_H

#include "expression.h"
#include "../interpreter/context.h"
#include "literal.h"

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
                          std::unique_ptr<Expression> second_op, std::shared_ptr<interpreter::Context> c);

        explicit OperatorOperation(std::unique_ptr<Expression> op, std::shared_ptr<interpreter::Context> c);

        std::string toString(int depth) override;

        std::shared_ptr<Value> evaluate() override;

    private:
        OperatorType type;
        std::unique_ptr<Expression> first_operand, second_operand;
        std::shared_ptr<interpreter::Context> context;

        std::shared_ptr<Value> checkTypesAndPerformOperation(std::shared_ptr<Value> val1, std::shared_ptr<Value> val2);

        std::shared_ptr<Value> negation(std::shared_ptr<Value> val);

        void assign(std::shared_ptr<Value> val);

        std::shared_ptr<Value>
        checkSymmetrically(std::shared_ptr<Value> val1, std::shared_ptr<Value> val2, bool swappedArgs = false);

        std::shared_ptr<Value> checkSameTypes(std::shared_ptr<Value> val1, std::shared_ptr<Value> val2);
    };

}

#endif //JEZYK_Z_CZASEM_OPERATOROPERATION_H
