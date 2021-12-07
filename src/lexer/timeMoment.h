#ifndef JEZYK_Z_CZASEM_TIMEMOMENT_H
#define JEZYK_Z_CZASEM_TIMEMOMENT_H

#include <ctime>

namespace lexer {

    struct TimeMoment {
        std::tm moment;

        int getYear() {
            return moment.tm_year;
        }

        int getMonth() {
            return moment.tm_mon;
        }

        int getDay() {
            return moment.tm_mday;
        }

        int getHour() {
            return moment.tm_hour;
        }

        int getMin() {
            return moment.tm_min;
        }

        int getSec() {
            return moment.tm_sec;
        }
    };
}

#endif //JEZYK_Z_CZASEM_TIMEMOMENT_H
