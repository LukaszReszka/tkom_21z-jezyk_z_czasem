#include <memory>
#include <utility>
#include "funccall.h"
#include "tln_exception.h"

namespace parser {
    FuncCall::FuncCall(std::string &f_name, std::vector<std::unique_ptr<Expression>> &args,
                       std::shared_ptr<interpreter::Context> c) : func_name(f_name), context(std::move(c)) {
        for (auto &a: args)
            this->args.push_back(std::move(a));
    }

    std::string FuncCall::toString(int depth) {
        std::string hyphens;
        for (int i = 0; i < depth; ++i)
            hyphens += "-";
        std::string text_rep = hyphens + "Function Call\n";
        hyphens += "-";
        text_rep += hyphens + "Name: " + func_name + "\n" + hyphens + "Arguments:\n";

        for (auto &a: args)
            text_rep += a->toString(depth + 2);

        return text_rep;
    }

    std::shared_ptr<Value> FuncCall::evaluate() {
        std::vector<std::string> params;
        std::vector<std::shared_ptr<Phrase>> body;

        if (!context->getFuncDef(func_name, params, body))
            throw tln_exception("Definition of function " + func_name + " not found\n");

        if (args.size() != params.size())
            throw tln_exception(
                    "Function " + func_name + " requires " + std::to_string(params.size()) + " arguments\n");

        std::vector<std::shared_ptr<Value>> args_val;
        for (auto &a: args)
            args_val.push_back(a->evaluate());

        context->addFunCallContext();
        for (int j = 0; j < params.size(); ++j)
            context->addVariable(params[j], args_val[j]);

        for (auto &instr: body)
            instr->execute();
        //TODO returning value ...
        context->removeFunCallContext();

        return {};
    }
}