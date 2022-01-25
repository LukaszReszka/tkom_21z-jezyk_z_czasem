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
            return std::to_string(value.int_s.count()) + "s";
        } else if (type == DATE || type == TIMESTAMP || type == CLOCK) {
            return timeMomentToString();
        } else if (type == INT_S) {
            return std::to_string(value.int_s.count()) + "s";
        } else if (type == INT_MIN) {
            return std::to_string(value.int_min.count()) + "m";
        } else if (type == INT_H) {
            return std::to_string(value.int_h.count()) + "h";
        } else if (type == DOUBLE_S) {
            return std::to_string(value.double_s.count()) + "s";
        } else if (type == DOUBLE_MIN) {
            return std::to_string(value.double_min.count()) + "m";
        } else if (type == DOUBLE_H) {
            return std::to_string(value.double_h.count()) + "h";
        }
        return "";
    }

    std::string Value::timeMomentToString() {
        std::string text_rep = "";
        int temp;
        if (type == DATE || type == TIMESTAMP) {
            temp = timeMoment.getDay();
            if (temp <= 9)
                text_rep += "0";
            text_rep += std::to_string(temp) + "/";

            temp = timeMoment.getMonth();
            if (temp <= 9)
                text_rep += "0";
            text_rep += std::to_string(temp) + "/";

            text_rep += std::to_string(timeMoment.getYear());

        }

        if (type == TIMESTAMP)
            text_rep += " ";

        if (type == CLOCK || type == TIMESTAMP) {
            temp = timeMoment.getHour();
            if (temp <= 9)
                text_rep += "0";
            text_rep += std::to_string(temp) + ":";

            temp = timeMoment.getMin();
            if (temp <= 9)
                text_rep += "0";
            text_rep += std::to_string(temp) + ":";

            temp = timeMoment.getSec();
            if (temp <= 9)
                text_rep += "0";
            text_rep += std::to_string(temp);

        }

        return text_rep;
    }
}