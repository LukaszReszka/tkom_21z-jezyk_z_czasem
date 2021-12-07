#ifndef JEZYK_Z_CZASEM_TIMEPERIOD_H
#define JEZYK_Z_CZASEM_TIMEPERIOD_H

#include <chrono>

struct TimePeriod {
    std::chrono::seconds s;
    std::chrono::minutes m;
    std::chrono::hours h;
};

#endif //JEZYK_Z_CZASEM_TIMEPERIOD_H
