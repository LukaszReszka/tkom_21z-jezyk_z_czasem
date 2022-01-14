#ifndef JEZYK_Z_CZASEM_LITERAL_H
#define JEZYK_Z_CZASEM_LITERAL_H

#include "value.h"
#include "expression.h"
#include <string>
#include <memory>

namespace parser {
    class Literal : public Expression {
    public:

        explicit Literal(std::string &text, ValueType t = ValueType::VARIABLE);

        explicit Literal(bool boolean);

        std::string toString() override;

        std::unique_ptr<Value> evaluate() override;

    private:
        std::unique_ptr<Value> val;
    };
}


#endif //JEZYK_Z_CZASEM_LITERAL_H
