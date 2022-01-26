#ifndef JEZYK_Z_CZASEM_RETURNINSTR_H
#define JEZYK_Z_CZASEM_RETURNINSTR_H

#include "phrase.h"
#include "expression.h"
#include "../interpreter/context.h"

namespace parser {
    class ReturnInstr : public Phrase {
    public:
        explicit ReturnInstr(std::unique_ptr<Expression> ret_val, std::shared_ptr<interpreter::Context> c);

        std::string toString(int depth) override;

        void execute() override;

    private:
        std::unique_ptr<Expression> returned_value;
        std::shared_ptr<interpreter::Context> context;
    };
}

#endif //JEZYK_Z_CZASEM_RETURNINSTR_H
