#include "scope.h"

namespace interpreter {

    void Scope::addVariableToScope(std::string &name, std::unique_ptr<Value> value) {
        std::shared_ptr<Value> val = std::move(value);
        variables[name] = val;
    }

    std::shared_ptr<Value> Scope::getVariableValue(std::string &var_name, bool &foundVariable) {
        auto v = variables.find(var_name);
        if (v == variables.end()) {
            foundVariable = false;
            return {};
        }
        
        foundVariable = true;
        return v->second;
    }
}