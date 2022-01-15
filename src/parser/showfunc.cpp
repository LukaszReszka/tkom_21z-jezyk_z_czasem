#include <memory>
#include <vector>
#include "showfunc.h"

namespace parser {

    ShowFunc::ShowFunc(std::vector<std::unique_ptr<Expression>> &args) : args(args) {}

    std::string ShowFunc::toString() {
        return std::string();
    }

    void ShowFunc::execute() {

    }
}