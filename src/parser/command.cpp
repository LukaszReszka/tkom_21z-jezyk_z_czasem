#include <string>
#include "command.h"

namespace parser {
    Command::Command(std::unique_ptr<FuncDef> fd) : type(FUNC_DEF), phrase(std::move(fd)) {}

    Command::Command(std::unique_ptr<Instruction> instr) : type(INSTRUCTION), phrase(std::move(instr)) {}

    std::string Command::toString(int depth) {
        std::string text_rep;
        if (std::holds_alternative<std::unique_ptr<Instruction>>(phrase))
            text_rep += std::get<std::unique_ptr<Instruction>>(phrase)->toString(depth);
        else
            text_rep += std::get<std::unique_ptr<FuncDef>>(phrase)->toString(depth);
        return text_rep;
    }

    void Command::execute() {

    }
}