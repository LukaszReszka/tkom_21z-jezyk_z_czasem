#include <memory>
#include <utility>
#include "funcdef.h"

namespace parser {
    FuncDef::FuncDef(std::string &name, std::vector<std::string> &params,
                     std::vector<std::unique_ptr<Phrase>> &body) : func_name(name), params(params) {
        for (auto &i: body)
            func_body.push_back(std::move(i));
    }

    std::string FuncDef::toString(int depth) {
        std::string hyphens;
        for (int i = 0; i < depth; ++i)
            hyphens += "-";
        std::string text_rep = hyphens + "Function Definition\n";
        hyphens += "-";
        text_rep += hyphens + "Name: " + func_name + "\n" + hyphens + "Parameters:\n";

        for (auto &p: params)
            text_rep += hyphens + "-" + p + "\n";

        text_rep += hyphens + "Function Body:\n";

        for (auto &i: func_body)
            text_rep += i->toString(depth + 2);

        return text_rep;
    }

    void FuncDef::execute() {

    }
}