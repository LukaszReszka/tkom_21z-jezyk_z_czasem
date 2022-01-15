#include <memory>
#include <utility>
#include "funcdef.h"

namespace parser {
    FuncDef::FuncDef(std::string &name, std::vector<std::string> &params,
                     std::vector<std::unique_ptr<Phrase>> &body) : func_name(name), params(params) {
        for (auto &i: body)
            func_body.push_back(std::move(i));
    }

    std::string FuncDef::toString() {
        return std::string();
    }

    void FuncDef::execute() {

    }
}