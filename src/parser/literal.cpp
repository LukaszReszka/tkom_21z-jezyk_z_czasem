#include "literal.h"
#include "tln_exception.h"
#include <utility>

namespace parser {

    Literal::Literal(std::shared_ptr<interpreter::Context> c) : context(std::move(c)) {
        val = std::make_unique<Value>();
    }

    Literal::Literal(lexer::TimeMoment &tm, ValueType type, std::shared_ptr<interpreter::Context> c) : context(
            std::move(c)) {
        val = std::make_unique<Value>();
        val->type = type;
        val->timeMoment = tm;
    }

    std::string Literal::toString(int depth) {
        std::string text_repr;
        for (int i = 0; i < depth; ++i)
            text_repr += "-";

        if (val->type == INT) {
            text_repr += "INT: ";
        } else if (val->type == DOUBLE) {
            text_repr += "DOUBLE: ";
        } else if (val->type == STRING) {
            text_repr += "STRING: ";
        } else if (val->type == BOOL) {
            text_repr += "BOOL: ";
        } else if (val->type == VARIABLE) {
            text_repr += "VARIABLE: ";
        } else if (val->type == TIME_PERIOD) {
            text_repr += "TIME_PERIOD[s]: ";
        } else if (val->type == DATE) {
            text_repr += "DATE: ";
        } else if (val->type == TIMESTAMP) {
            text_repr += "TIMESTAMP: ";
        } else if (val->type == CLOCK) {
            text_repr += "CLOCK: ";
        } else if (val->type == INT_S) {
            text_repr += "SECONDS(int): ";
        } else if (val->type == INT_MIN) {
            text_repr += "MINUTES(int): ";
        } else if (val->type == INT_H) {
            text_repr += "HOURS(int): ";
        } else if (val->type == DOUBLE_S) {
            text_repr += "SECONDS(double): ";
        } else if (val->type == DOUBLE_MIN) {
            text_repr += "MINUTES(double): ";
        } else if (val->type == DOUBLE_H) {
            text_repr += "HOURS(double): ";
        }
        text_repr += val->toString();
        return text_repr + "\n";
    }

    std::shared_ptr<Value> Literal::evaluate() {
        if (val->type != VARIABLE)
            return std::move(val);

        bool foundVarVal = false;
        std::shared_ptr<Value> v = context->getVariableValue(val->value_str, foundVarVal);

        if (!foundVarVal)
            throw tln_exception("Not found variable " + val->value_str);

        return v;
    }
}