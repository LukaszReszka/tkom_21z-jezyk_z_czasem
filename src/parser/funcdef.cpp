#include <memory>
#include <string>
#include "funcdef.h"

namespace parser {
    FuncDef::FuncDef(std::string &name, std::vector<std::string> &params,
                     std::vector<std::unique_ptr<Phrase>> &body)
            : func_name(name), params(params), func_body(body) {}

    std::string FuncDef::toString() {
        return std::string();
    }

    void FuncDef::execute() {

    }
}