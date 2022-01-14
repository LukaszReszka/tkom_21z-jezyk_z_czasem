#ifndef JEZYK_Z_CZASEM_EXPRESSION_H
#define JEZYK_Z_CZASEM_EXPRESSION_H

#include <memory>
#include "value.h"

namespace parser {
    class Expression {
    public:

        virtual std::string toString() = 0;

        virtual std::unique_ptr<Value> evaluate() = 0;

        inline std::ostream &operator<<(std::ostream &os) {
            return os << toString();
        }

    };
}

#endif //JEZYK_Z_CZASEM_EXPRESSION_H
