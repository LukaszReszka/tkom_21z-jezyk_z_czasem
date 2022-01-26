#ifndef JEZYK_Z_CZASEM_TIMEMOMENT_H
#define JEZYK_Z_CZASEM_TIMEMOMENT_H

#include <ctime>

namespace lexer {

    struct TimeMoment {
        TimeMoment() {
            moment.tm_year = 0;
            moment.tm_mon = 0;
            moment.tm_mday = 2;
            moment.tm_hour = 12;
            moment.tm_min = 0;
            moment.tm_sec = 0;
        }

        std::tm moment{0};

        [[nodiscard]] int getYear() const {
            return moment.tm_year + 1900;
        }

        [[nodiscard]] int getMonth() const {
            return moment.tm_mon + 1;
        }

        [[nodiscard]] int getDay() const {
            return moment.tm_mday;
        }

        [[nodiscard]] int getHour() const {
            return moment.tm_hour;
        }

        [[nodiscard]] int getMin() const {
            return moment.tm_min;
        }

        [[nodiscard]] int getSec() const {
            return moment.tm_sec;
        }

        void setYear(int year_since_1900) {
            moment.tm_year = year_since_1900 - 1900;
        }

        void setMonth(int month) {
            moment.tm_mon = month - 1;
        }

        void setDay(int day) {
            moment.tm_mday = day;
        }

        void setHour(int hour_since_midnight) {
            moment.tm_hour = hour_since_midnight;
        }

        void setMin(int min_after_hour) {
            moment.tm_min = min_after_hour;
        }

        void setSec(int seconds_after_minute) {
            moment.tm_sec = seconds_after_minute;
        }
    };
}

#endif //JEZYK_Z_CZASEM_TIMEMOMENT_H
