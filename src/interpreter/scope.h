#ifndef JEZYK_Z_CZASEM_SCOPE_H
#define JEZYK_Z_CZASEM_SCOPE_H

#include <memory>
#include "../parser/value.h"

using parser::Value;

namespace interpreter {
    class Scope {
    public:

        void addVariableToScope(std::string &name, std::unique_ptr<Value> value);

        std::shared_ptr<Value> getVariableValue(std::string &var_name, bool &foundVariable);

    private:
        std::map<std::string, std::shared_ptr<Value>> variables;
    };
}

#endif //JEZYK_Z_CZASEM_SCOPE_H
