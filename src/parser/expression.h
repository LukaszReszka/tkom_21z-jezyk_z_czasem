#ifndef JEZYK_Z_CZASEM_EXPRESSION_H
#define JEZYK_Z_CZASEM_EXPRESSION_H

#include "value.h"
#include <memory>

namespace parser {
    class Expression {
    public:

        virtual std::string toString(int depth) = 0;

        virtual std::shared_ptr<Value> evaluate() = 0;
    };
}

#endif //JEZYK_Z_CZASEM_EXPRESSION_H
