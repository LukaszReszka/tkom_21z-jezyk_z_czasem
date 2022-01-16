#include <memory>
#include <utility>
#include "funccall.h"

namespace parser {
    FuncCall::FuncCall(std::string &f_name, std::vector<std::string> &args, std::shared_ptr<interpreter::Context> c) :
            func_name(f_name), args(args), context(std::move(c)) {}

    std::string FuncCall::toString(int depth) {
        std::string hyphens;
        for (int i = 0; i < depth; ++i)
            hyphens += "-";
        std::string text_rep = hyphens + "Function Call\n";
        hyphens += "-";
        text_rep += hyphens + "Name: " + func_name + "\n" + hyphens + "Arguments:\n";
        hyphens += "-";

        for (auto &a: args)
            text_rep += hyphens + a + "\n";

        return text_rep;
    }

    std::unique_ptr<Value> FuncCall::evaluate() {
        return std::unique_ptr<Value>();
    }
}