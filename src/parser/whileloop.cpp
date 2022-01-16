#include <memory>
#include <utility>
#include <vector>
#include "whileloop.h"

namespace parser {

    WhileLoop::WhileLoop(std::unique_ptr<Expression> cond, std::vector<std::unique_ptr<Phrase>> &body,
                         std::shared_ptr<interpreter::Context> c) : cond(std::move(cond)), context(std::move(c)) {
        for (auto &i: body)
            this->body.push_back(std::move(i));
    }

    std::string WhileLoop::toString(int depth) {
        std::string hyphens;
        for (int i = 0; i < depth; ++i)
            hyphens += "-";
        std::string text_rep = hyphens + "WHILE\n";
        hyphens += "-";
        text_rep += hyphens + "Condition:\n" + cond->toString(depth + 2) + hyphens + "Body:\n";

        for (auto &i: body)
            text_rep += i->toString(depth + 2);

        return text_rep;
    }

    void WhileLoop::execute() {

    }
}