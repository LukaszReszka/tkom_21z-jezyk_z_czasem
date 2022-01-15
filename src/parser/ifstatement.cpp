#include <memory>
#include "ifstatement.h"

namespace parser {

    IfStatement::IfStatement(std::unique_ptr<Expression> cond, std::vector<std::unique_ptr<Phrase>> &body,
                             std::vector<std::unique_ptr<ElifStat>> &elifs) : cond(std::move(cond)) {
        for (auto &i: body)
            this->body.push_back(std::move(i));

        for (auto &j: elifs)
            this->elifs.push_back(std::move(j));
    }

    std::string IfStatement::toString(int depth) {
        std::string hyphens;
        while (depth--)
            hyphens += "-";
        std::string text_rep = hyphens + "IF\n";
        hyphens += "-";
        text_rep += hyphens + "Condition:\n" + cond->toString(depth + 2) + hyphens + "Body:\n";

        for (auto &i: body)
            text_rep += i->toString(depth + 2);

        for (auto &e: elifs)
            text_rep += e->toString(depth + 2);

        return text_rep;
    }

    void IfStatement::execute() {

    }
}