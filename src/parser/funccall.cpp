#include <memory>
#include "funccall.h"

namespace parser {
    FuncCall::FuncCall(std::string &f_name, std::vector<std::string> &args) : func_name(f_name), args(args) {}

    std::string FuncCall::toString() {
        return std::string();
    }

    std::unique_ptr<Value> FuncCall::evaluate() {
        return std::unique_ptr<Value>();
    }
}