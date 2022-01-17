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

    std::shared_ptr<Value> FuncCall::evaluate() {
        std::vector<std::string> params;
        std::vector<std::shared_ptr<Phrase>> body;

        if (!context->getFuncDef(func_name, params, body))
            throw std::runtime_error("Definition of function " + func_name + " not found\n");

        if (args.size() != params.size())
            throw std::runtime_error(
                    "Function " + func_name + " requires " + std::to_string(params.size()) + " arguments\n");

        std::vector<std::shared_ptr<Value>> args_val;
        for (int i = 0; i < params.size(); ++i) {
            bool foundArgumentValue = false;
            args_val.push_back(context->getVariableValue(args[i], foundArgumentValue));
            if (!foundArgumentValue)
                throw std::runtime_error(
                        "Function call " + func_name + ": value of argument " + std::to_string(i) + " not found\n");
        }

        context->addFunCallContext();
        for (int j = 0; j < params.size(); ++j)
            context->addVariable(params[j], args_val[j]);

        for (auto &instr: body)
            instr->execute();

        context->removeFunCallContext();

        return {};
    }
}