#ifndef JEZYK_Z_CZASEM_FUNCALLCONTEXT_H
#define JEZYK_Z_CZASEM_FUNCALLCONTEXT_H

#include "scope.h"
#include <vector>

namespace interpreter {
    class FunCallContext {
    public:

        FunCallContext() { func_scope.emplace_back(); }

        inline void addScopeToContext() { func_scope.emplace_back(); }

        inline void removeScopeFromContext() { func_scope.pop_back(); }

        inline void addVariable(std::string &name, std::unique_ptr<Value> value) {
            func_scope.back().addVariableToScope(name, std::move(value));
        }

        void addVariable(std::string &name, std::shared_ptr<Value> value);

        std::shared_ptr<Value> getVariableValue(std::string &var_name, bool &foundVariable);

    private:
        std::vector<Scope> func_scope;
    };

}


#endif //JEZYK_Z_CZASEM_FUNCALLCONTEXT_H
