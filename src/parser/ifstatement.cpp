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

    std::string IfStatement::toString() {
        return std::string();
    }

    void IfStatement::execute() {

    }
}