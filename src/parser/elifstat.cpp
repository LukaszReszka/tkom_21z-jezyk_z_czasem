#include <memory>
#include <string>
#include <utility>
#include "elifstat.h"

namespace parser {

    ElifStat::ElifStat(std::unique_ptr<Expression> cond, std::vector<std::unique_ptr<Phrase>> &body) : cond(
            std::move(cond)) {
        for (auto &i: body)
            this->body.push_back(std::move(i));
    }

    std::string ElifStat::toString() {
        return std::string();
    }

    void ElifStat::execute() {

    }
}