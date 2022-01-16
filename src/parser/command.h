#ifndef JEZYK_Z_CZASEM_COMMAND_H
#define JEZYK_Z_CZASEM_COMMAND_H

#include <memory>
#include "funcdef.h"
#include "../interpreter/context.h"

namespace parser {
    class Command : public Phrase {
    public:
        explicit Command(std::unique_ptr<FuncDef> fd, std::shared_ptr<interpreter::Context> c);

        explicit Command(std::unique_ptr<Instruction> instr, std::shared_ptr<interpreter::Context> c);

        std::string toString(int depth) override;

        void execute() override;

    private:
        enum Type {
            FUNC_DEF,
            INSTRUCTION
        } type;

        std::variant<std::unique_ptr<FuncDef>, std::unique_ptr<Instruction>> phrase;

        std::shared_ptr<interpreter::Context> context;
    };
}

#endif //JEZYK_Z_CZASEM_COMMAND_H
