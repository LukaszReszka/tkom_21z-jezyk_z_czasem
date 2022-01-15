#include <memory>
#include "instruction.h"

namespace parser {

    Instruction::Instruction(std::unique_ptr<Phrase> instr) : instruction(std::move(instr)) {}

    Instruction::Instruction(std::unique_ptr<Expression> instr) : instruction(std::move(instr)) {}

    std::string Instruction::toString(int depth) {
        std::string text_rep;
        if (std::holds_alternative<std::unique_ptr<Phrase>>(instruction))
            text_rep += std::get<std::unique_ptr<Phrase>>(instruction)->toString(depth);
        else
            text_rep += std::get<std::unique_ptr<Expression>>(instruction)->toString(depth);
        return text_rep;
    }

    void Instruction::execute(std::shared_ptr<interpreter::Context> cont) {

    }
}