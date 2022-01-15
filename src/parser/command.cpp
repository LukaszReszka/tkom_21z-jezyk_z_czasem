#include <string>
#include "command.h"

namespace parser {
    Command::Command(std::unique_ptr<FuncDef> fd) : type(FUNC_DEF), phrase(std::move(fd)) {}

    Command::Command(std::unique_ptr<Instruction> instr) : type(INSTRUCTION), phrase(std::move(instr)) {}

    std::string Command::toString() {
        return nullptr;
    }

    void Command::execute() {

    }
}