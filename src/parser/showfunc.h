#ifndef JEZYK_Z_CZASEM_SHOWFUNC_H
#define JEZYK_Z_CZASEM_SHOWFUNC_H

#include "phrase.h"
#include "expression.h"

namespace parser {
    class ShowFunc : public Phrase {
    public:

        explicit ShowFunc(std::vector<std::unique_ptr<Expression>> &args);

        std::string toString(int depth) override;

        void execute(std::shared_ptr<interpreter::Context> cont) override;

    private:

        std::vector<std::unique_ptr<Expression>> args;
    };
}

#endif //JEZYK_Z_CZASEM_SHOWFUNC_H
