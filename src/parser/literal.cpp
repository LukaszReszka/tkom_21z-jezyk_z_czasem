#include "literal.h"

namespace parser {

    std::string Literal::toString() {
        return std::string();
    }

    std::unique_ptr<Value> Literal::evaluate() {
        return std::unique_ptr<Value>();
    }

    Literal::Literal(std::string &text, ValueType t) {
        val->type = t;
        val->value.text = text;
    }

    Literal::Literal(bool boolean) {
        val->type = BOOL;
        val->value.boolean = boolean;
    }
}