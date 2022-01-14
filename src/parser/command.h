#ifndef JEZYK_Z_CZASEM_COMMAND_H
#define JEZYK_Z_CZASEM_COMMAND_H

#include "phrase.h"
#include "funcdef.h"
#include "phrase.h"
#include <string>
#include <variant>
#include <memory>

namespace parser {
    class Command : public Phrase {
    public:
        explicit Command(std::unique_ptr<FuncDef> fd);

        explicit Command(std::unique_ptr<Instruction> instr);

        std::string toString() override;

        void execute() override;

    private:
        enum Type {
            FUNC_DEF,
            INSTRUCTION
        } type;

        std::variant<std::unique_ptr<FuncDef>, std::unique_ptr<Instruction>> phrase;
    };
}

#endif //JEZYK_Z_CZASEM_COMMAND_H
