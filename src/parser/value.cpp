#include "value.h"

namespace parser {

    std::string Value::toString() {
        if (type == INT) {
            return std::to_string(value.integer_numb);
        } else if (type == DOUBLE) {
            return std::to_string(value.double_numb);
        } else if (type == STRING || type == VARIABLE) {
            return value_str;
        } else if (type == BOOL) {
            return std::to_string(value.boolean);
        } else if (type == TIME_PERIOD) {
            return std::to_string(value.int_s.count());
        } else if (type == DATE) {
            lexer::TimeMoment tm = timeMoment;
            return std::to_string(tm.getDay()) + "/" + std::to_string(tm.getMonth()) + "/" +
                   std::to_string(tm.getYear());
        } else if (type == TIMESTAMP) {
            lexer::TimeMoment tm = timeMoment;
            return std::to_string(tm.getDay()) + "/" + std::to_string(tm.getMonth()) + "/" +
                   std::to_string(tm.getYear()) + " " + std::to_string(tm.getHour()) + ":" +
                   std::to_string(tm.getMin()) + ":" +
                   std::to_string(tm.getSec());
        } else if (type == CLOCK) {
            lexer::TimeMoment tm = timeMoment;
            return std::to_string(tm.getHour()) + ":" + std::to_string(tm.getMin()) + ":" +
                   std::to_string(tm.getSec());
        } else if (type == INT_S) {
            return std::to_string(value.int_s.count());
        } else if (type == INT_MIN) {
            return std::to_string(value.int_min.count());
        } else if (type == INT_H) {
            return std::to_string(value.int_h.count());
        } else if (type == DOUBLE_S) {
            return std::to_string(value.double_s.count());
        } else if (type == DOUBLE_MIN) {
            return std::to_string(value.double_min.count());
        } else if (type == DOUBLE_H) {
            return std::to_string(value.double_h.count());
        }
        return "";
    }
}