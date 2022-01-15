#include <memory>
#include "instruction.h"

namespace parser {

    Instruction::Instruction(std::unique_ptr<Phrase> instr) : instruction(std::move(instr)) {}

    Instruction::Instruction(std::unique_ptr<Expression> instr) : instruction(std::move(instr)) {}

    std::string Instruction::toString() {
        return std::string();
    }

    void Instruction::execute() {

    }
}