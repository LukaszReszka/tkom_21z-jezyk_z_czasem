#include "context.h"

namespace interpreter {

    void Context::saveFuncDef(std::string &name, std::vector<std::string> &params,
                              std::vector<std::unique_ptr<Phrase>> &body) {

        std::vector<std::shared_ptr<Phrase>> shared_body;
        for (auto &i: body)
            shared_body.push_back(std::move(i));

        func_defs[name] = std::make_tuple(params, shared_body);
    }

    bool Context::getFuncDef(std::string &name, std::vector<std::string> &params,
                             std::vector<std::shared_ptr<Phrase>> &body) {
        params.clear();
        body.clear();

        auto fd = func_defs.find(name);
        if (fd == func_defs.end())
            return false;

        params = std::get<0>(fd->second);
        body = std::get<1>(fd->second);
        return true;
    }

    void Context::addScope() {
        if (funcs_context.empty())
            global_scopes.addScopeToContext();
        else
            funcs_context.back().addScopeToContext();

    }

    void Context::removeScope() {
        if (funcs_context.empty())
            global_scopes.removeScopeFromContext();
        else
            funcs_context.back().removeScopeFromContext();

    }

    void Context::addVariable(std::string &name, std::unique_ptr<Value> value) {
        if (funcs_context.empty())
            global_scopes.addVariable(name, std::move(value));
        else
            funcs_context.back().addVariable(name, std::move(value));
    }

    void Context::addVariable(std::string &name, std::shared_ptr<Value> value) {
        if (funcs_context.empty())
            global_scopes.addVariable(name, std::move(value));
        else
            funcs_context.back().addVariable(name, std::move(value));
    }

    std::shared_ptr<Value> Context::getVariableValue(std::string &var_name, bool &foundVariable) {
        foundVariable = false;
        if (!funcs_context.empty()) {
            std::shared_ptr<Value> val = funcs_context.back().getVariableValue(var_name, foundVariable);
            if (foundVariable)
                return val;
        }

        std::shared_ptr<Value> val = global_scopes.getVariableValue(var_name, foundVariable);
        if (foundVariable)
            return val;

        return {};
    }

    void Context::addFunCallContext() {
        funcs_context.emplace_back();
    }

    void Context::removeFunCallContext() {
        if (!funcs_context.empty()) {
            funcs_context.pop_back();
            endProgramExecution = false;
            returned_value = std::make_shared<Value>();
        }
    }
}