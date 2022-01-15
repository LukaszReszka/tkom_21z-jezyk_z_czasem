#include <memory>
#include <utility>
#include <vector>
#include "showfunc.h"

namespace parser {

    ShowFunc::ShowFunc(std::vector<std::unique_ptr<Expression>> &args) {
        for (auto &a: args)
            this->args.push_back(std::move(a));
    }

    std::string ShowFunc::toString(int depth) {
        std::string hyphens;
        while (depth--)
            hyphens += "-";
        std::string text_rep = hyphens + "SHOW\n" + hyphens + "-Arguments:\n";

        for (auto &a: args)
            text_rep += a->toString(depth + 2);

        return text_rep;
    }

    void ShowFunc::execute() {

    }
}