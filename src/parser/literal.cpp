#include "literal.h"

namespace parser {

    Literal::Literal(lexer::TimeMoment &tm, ValueType type) {
        val = std::make_unique<Value>();
        val->type = type;
        val->timeMoment = tm;
    }

    std::string Literal::toString(int depth) {
        std::string text_repr;
        for (int i = 0; i < depth; ++i)
            text_repr += "-";

        if (val->type == INT) {
            text_repr += "INT: " + std::to_string(val->value.integer_numb);
        } else if (val->type == DOUBLE) {
            text_repr += "DOUBLE: " + std::to_string(val->value.double_numb);
        } else if (val->type == STRING) {
            text_repr += "STRING: " + val->value_str;
        } else if (val->type == BOOL) {
            text_repr += "BOOL: " + std::to_string(val->value.boolean);
        } else if (val->type == VARIABLE) {
            text_repr += "VARIABLE: " + val->value_str;
        } else if (val->type == TIME_PERIOD) {
            text_repr += "TIME_PERIOD [s]: " + std::to_string(val->value.int_s.count());
        } else if (val->type == DATE) {
            lexer::TimeMoment tm = val->timeMoment;
            text_repr += "DATE: " + std::to_string(tm.getDay()) + "/" + std::to_string(tm.getMonth()) + "/" +
                         std::to_string(tm.getYear());
        } else if (val->type == TIMESTAMP) {
            lexer::TimeMoment tm = val->timeMoment;
            text_repr += "TIMESTAMP: " + std::to_string(tm.getDay()) + "/" + std::to_string(tm.getMonth()) + "/" +
                         std::to_string(tm.getYear()) + " " + std::to_string(tm.getHour()) + ":" +
                         std::to_string(tm.getMin()) + ":" +
                         std::to_string(tm.getSec());
        } else if (val->type == CLOCK) {
            lexer::TimeMoment tm = val->timeMoment;
            text_repr += "CLOCK: " + std::to_string(tm.getHour()) + ":" + std::to_string(tm.getMin()) + ":" +
                         std::to_string(tm.getSec());
        } else if (val->type == INT_S) {
            text_repr += "SECONDS (int): " + std::to_string(val->value.int_s.count());
        } else if (val->type == INT_MIN) {
            text_repr += "MINUTES (int): " + std::to_string(val->value.int_min.count());
        } else if (val->type == INT_H) {
            text_repr += "HOURS (int): " + std::to_string(val->value.int_h.count());
        } else if (val->type == DOUBLE_S) {
            text_repr += "SECONDS (double): " + std::to_string(val->value.double_s.count());
        } else if (val->type == DOUBLE_MIN) {
            text_repr += "MINUTES (double): " + std::to_string(val->value.double_min.count());
        } else if (val->type == DOUBLE_H) {
            text_repr += "HOURS (double): " + std::to_string(val->value.double_h.count());
        }

        return text_repr + "\n";
    }

    std::unique_ptr<Value> Literal::evaluate(std::shared_ptr<interpreter::Context> cont) {
        return std::unique_ptr<Value>();
    }
}