#ifndef JEZYK_Z_CZASEM_FUNCCALL_H
#define JEZYK_Z_CZASEM_FUNCCALL_H

#include "expression.h"
#include "../interpreter/context.h"
#include <vector>

namespace parser {
    class FuncCall : public Expression {
    public:

        FuncCall(std::string &f_name, std::vector<std::string> &args, std::shared_ptr<interpreter::Context> c);

        std::string toString(int depth) override;

        std::unique_ptr<Value> evaluate() override;

    private:
        std::string func_name;
        std::vector<std::string> args;
        std::shared_ptr<interpreter::Context> context;
    };
}

#endif //JEZYK_Z_CZASEM_FUNCCALL_H
