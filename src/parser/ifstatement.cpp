#include "ifstatement.h"

namespace parser {

    IfStatement::IfStatement(std::unique_ptr<Expression> cond, std::vector<std::unique_ptr<Phrase>> &body,
                             std::vector<std::unique_ptr<ElifStat>> &elifs) : cond(std::move(cond)), body(body),
                                                                              elifs(elifs) {}

    std::string IfStatement::toString() {
        return std::string();
    }

    void IfStatement::execute() {

    }
}