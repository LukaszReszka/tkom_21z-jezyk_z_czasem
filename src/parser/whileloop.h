#ifndef JEZYK_Z_CZASEM_WHILELOOP_H
#define JEZYK_Z_CZASEM_WHILELOOP_H

#include "phrase.h"
#include "expression.h"

namespace parser {
    class WhileLoop : public Phrase {
    public:

        WhileLoop(std::unique_ptr<Expression> cond, std::vector<std::unique_ptr<Phrase>> &body);

        std::string toString(int depth) override;

        void execute() override;

    private:
        std::unique_ptr<Expression> cond;
        std::vector<std::unique_ptr<Phrase>> body;
    };
}

#endif //JEZYK_Z_CZASEM_WHILELOOP_H
