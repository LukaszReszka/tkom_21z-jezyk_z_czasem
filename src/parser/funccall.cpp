#include <memory>
#include "funccall.h"

namespace parser {
    FuncCall::FuncCall(std::string &f_name, std::vector<std::string> &args) : func_name(f_name), args(args) {}

    std::string FuncCall::toString(int depth) {
        std::string hyphens;
        while (depth--)
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