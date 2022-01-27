#include "funcallcontext.h"

namespace interpreter {

    std::shared_ptr<Value> FunCallContext::getVariableValue(std::string &var_name, bool &foundVariable) {
        foundVariable = false;
        for (auto it = func_scope.rbegin(); it != func_scope.rend(); ++it) {
            std::shared_ptr<Value> val = it->getVariableValue(var_name, foundVariable);
            if (foundVariable)
                return val;
        }

        return {};
    }

    void FunCallContext::addVariable(std::string &name, std::shared_ptr<Value> value) {
        bool foundVariable = false;
        for (auto it = func_scope.rbegin(); it != func_scope.rend(); ++it) {
            it->getVariableValue(name, foundVariable);
            if (foundVariable) {
                it->addVariableToScope(name, value);
                return;
            }
        }

        func_scope.back().addVariableToScope(name, std::move(value));
    }
}