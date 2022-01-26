#include <memory>
#include <utility>
#include "ifstatement.h"

namespace parser {

    IfStatement::IfStatement(std::unique_ptr<Expression> cond, std::vector<std::unique_ptr<Phrase>> &body,
                             std::vector<std::unique_ptr<ElifStat>> &elifs, std::shared_ptr<interpreter::Context> c)
            : cond(std::move(cond)), context(std::move(c)) {
        for (auto &i: body)
            this->body.push_back(std::move(i));

        for (auto &j: elifs)
            this->elifs.push_back(std::move(j));
    }

    std::string IfStatement::toString(int depth) {
        std::string hyphens;
        for (int i = 0; i < depth; ++i)
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
        if (cond->evaluate()->value.boolean) {
            context->addScope();
            for (auto &i: body) {
                i->execute();
                if (context->endProgramExecution)
                    break;
            }
            context->removeScope();
        } else {
            for (auto &elif: elifs) {
                if (elif->evaluateCondition()) {
                    elif->execute();
                    break;
                }
            }
        }
    }
}