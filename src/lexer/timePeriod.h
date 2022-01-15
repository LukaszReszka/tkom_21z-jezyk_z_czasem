#ifndef JEZYK_Z_CZASEM_TIMEPERIOD_H
#define JEZYK_Z_CZASEM_TIMEPERIOD_H

#include <chrono>

namespace lexer {

    struct TimePeriod {
        std::chrono::seconds s = std::chrono::seconds(0);
        std::chrono::minutes m = std::chrono::minutes(0);
        std::chrono::hours h = std::chrono::hours(0);

        [[nodiscard]] inline std::chrono::seconds getSecNumb() const {
            return h + m + s;
        }
    };
}

#endif //JEZYK_Z_CZASEM_TIMEPERIOD_H
