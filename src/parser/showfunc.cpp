#include <memory>
#include <utility>
#include <vector>
#include "showfunc.h"

namespace parser {

    ShowFunc::ShowFunc(std::vector<std::unique_ptr<Expression>> &args) {
        for (auto &a: args)
            this->args.push_back(std::move(a));
    }

    std::string ShowFunc::toString() {
        return std::string();
    }

    void ShowFunc::execute() {

    }
}