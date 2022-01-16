#ifndef JEZYK_Z_CZASEM_CONTEXT_H
#define JEZYK_Z_CZASEM_CONTEXT_H

#include <map>
#include <vector>
#include "../parser/phrase.h"
#include "../parser/value.h"
#include "funcallcontext.h"

using parser::Phrase;

namespace interpreter {
    class Context {
    public:

        bool reachedFinalReturn = false;

        void saveFuncDef(std::string &name, std::vector<std::string> &params,
                         std::vector<std::unique_ptr<Phrase>> &body);

        bool getFuncDef(std::string &name, std::vector<std::string> &params,
                        std::vector<std::shared_ptr<Phrase>> &body);

        void addScope();

        void removeScope();

        void addVariable(std::string &name, std::unique_ptr<Value> value);

        std::shared_ptr<Value> getVariableValue(std::string &var_name, bool &foundVariable);


    private:
        std::map<std::string, std::tuple<std::vector<std::string>, std::vector<std::shared_ptr<Phrase>>>> func_defs;

        FunCallContext global_scopes;
        std::vector<FunCallContext> funcs_context;

    };
}


#endif //JEZYK_Z_CZASEM_CONTEXT_H
