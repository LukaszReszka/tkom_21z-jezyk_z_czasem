#ifndef JEZYK_Z_CZASEM_VALUE_H
#define JEZYK_Z_CZASEM_VALUE_H

#include <chrono>
#include "../lexer/lexer.h"

using std::chrono::seconds, std::chrono::minutes, std::chrono::hours;
using std::ratio, std::chrono::duration;

namespace parser {
    enum ValueType {
        INT, DOUBLE,
        STRING, BOOL,
        TIME_PERIOD, DATE, TIMESTAMP, CLOCK,
        INT_S, INT_MIN, INT_H,
        DOUBLE_S, DOUBLE_MIN, DOUBLE_H,
        VARIABLE
    };

    struct Value {
    public:

        ValueType type;

        union val {
            int integer_numb;
            bool boolean;
            double double_numb;
            seconds int_s;
            minutes int_min;
            hours int_h;
            duration<double> double_s;
            duration<double, ratio<60>> double_min;
            duration<double, ratio<3600>> double_h;
        } value;

        std::string value_str;
        lexer::TimeMoment timeMoment;
    };
}

#endif //JEZYK_Z_CZASEM_VALUE_H
