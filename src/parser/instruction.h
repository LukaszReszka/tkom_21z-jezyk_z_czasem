#ifndef JEZYK_Z_CZASEM_INSTRUCTION_H
#define JEZYK_Z_CZASEM_INSTRUCTION_H

#include "funccall.h"
#include "returninstr.h"
#include "showfunc.h"
#include "whileloop.h"

namespace parser {
    class Instruction : public Phrase {
    public:

        Instruction(std::unique_ptr<Phrase> instr);

        Instruction(std::unique_ptr<Expression> instr);

        std::string toString() override;

        void execute() override;

    private:

        std::variant<std::unique_ptr<Expression>, std::unique_ptr<Phrase>> instruction;
    };
}

#endif //JEZYK_Z_CZASEM_INSTRUCTION_H
