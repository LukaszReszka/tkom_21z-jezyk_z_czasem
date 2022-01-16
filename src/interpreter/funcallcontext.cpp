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
}