#ifndef JEZYK_Z_CZASEM_TIMEMOMENT_H
#define JEZYK_Z_CZASEM_TIMEMOMENT_H

#include <ctime>

namespace lexer {

    struct TimeMoment {
        std::tm moment;

        int getYear() const {
            return moment.tm_year;
        }

        int getMonth() const {
            return moment.tm_mon;
        }

        int getDay() const {
            return moment.tm_mday;
        }

        int getHour() const {
            return moment.tm_hour;
        }

        int getMin() const {
            return moment.tm_min;
        }

        int getSec() const {
            return moment.tm_sec;
        }
    };
}

#endif //JEZYK_Z_CZASEM_TIMEMOMENT_H
