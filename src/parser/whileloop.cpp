#include "whileloop.h"

namespace parser {

    WhileLoop::WhileLoop(std::unique_ptr<Expression> cond, std::vector<std::unique_ptr<Phrase>> &body) : cond(
            std::move(cond)), body(body) {}

    std::string WhileLoop::toString() {
        return std::string();
    }

    void WhileLoop::execute() {

    }
}