#ifndef JEZYK_Z_CZASEM_RETURNINSTR_H
#define JEZYK_Z_CZASEM_RETURNINSTR_H

#include "phrase.h"
#include "expression.h"

namespace parser {
    class ReturnInstr : public Phrase {
    public:
        explicit ReturnInstr(std::unique_ptr<Expression> ret_val);

        std::string toString(int depth) override;

        void execute() override;

    private:
        std::unique_ptr<Expression> returned_value;
    };
}

#endif //JEZYK_Z_CZASEM_RETURNINSTR_H
