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

    std::string ElifStat::toString(int depth) {
        std::string hyphens;
        while (depth--)
            hyphens += "-";
        std::string text_rep = hyphens + "ELIF\n";
        hyphens += "-";
        text_rep += hyphens + "Condition:\n" + cond->toString(depth + 2) + hyphens + "Body:\n";

        for (auto &i: body)
            text_rep += i->toString(depth + 2);

        return text_rep;
    }

    void ElifStat::execute() {

    }
}