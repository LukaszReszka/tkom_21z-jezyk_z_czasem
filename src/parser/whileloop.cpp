#include <memory>
#include <utility>
#include <vector>
#include "whileloop.h"

namespace parser {

    WhileLoop::WhileLoop(std::unique_ptr<Expression> cond, std::vector<std::unique_ptr<Phrase>> &body) : cond(
            std::move(cond)) {
        for (auto &i: body)
            this->body.push_back(std::move(i));
    }

    std::string WhileLoop::toString() {
        return std::string();
    }

    void WhileLoop::execute() {

    }
}