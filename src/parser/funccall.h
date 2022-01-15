#ifndef JEZYK_Z_CZASEM_FUNCCALL_H
#define JEZYK_Z_CZASEM_FUNCCALL_H

#include "expression.h"
#include <vector>

namespace parser {
    class FuncCall : public Expression {
    public:

        FuncCall(std::string &f_name, std::vector<std::string> &args);

        std::string toString(int depth) override;

        std::unique_ptr<Value> evaluate() override;

    private:
        std::string func_name;
        std::vector<std::string> args;

    };
}

#endif //JEZYK_Z_CZASEM_FUNCCALL_H
