#include <memory>
#include <string>
#include <utility>
#include "elifstat.h"

namespace parser {

    ElifStat::ElifStat(std::unique_ptr<Expression> cond, std::vector<std::unique_ptr<Phrase>> &body,
                       std::shared_ptr<interpreter::Context> c) : cond(std::move(cond)), context(std::move(c)) {
        for (auto &i: body)
            this->body.push_back(std::move(i));
    }

    std::string ElifStat::toString(int depth) {
        std::string hyphens;
        for (int i = 0; i < depth; ++i)
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