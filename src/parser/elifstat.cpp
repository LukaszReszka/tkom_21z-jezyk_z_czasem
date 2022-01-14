#include "elifstat.h"

namespace parser {

    ElifStat::ElifStat(std::unique_ptr<Expression> cond, std::vector<std::unique_ptr<Phrase>> &body) : cond(
            std::move(cond)), body(body) {}

    std::string ElifStat::toString() {
        return std::string();
    }

    void ElifStat::execute() {

    }
}