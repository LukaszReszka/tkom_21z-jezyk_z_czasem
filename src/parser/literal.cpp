#include "literal.h"

namespace parser {

    Literal::Literal(lexer::TimeMoment &tm, ValueType type) {
        val->type = type;
        val->value.timeMoment = tm;
    }

    std::string Literal::toString() {
        return std::string();
    }

    std::unique_ptr<Value> Literal::evaluate() {
        return std::unique_ptr<Value>();
    }
}