#include <string>
#include <utility>
#include "command.h"

namespace parser {
    Command::Command(std::unique_ptr<FuncDef> fd, std::shared_ptr<interpreter::Context> c)
            : type(FUNC_DEF), phrase(std::move(fd)), context(std::move(c)) {}

    Command::Command(std::unique_ptr<Instruction> instr, std::shared_ptr<interpreter::Context> c)
            : type(INSTRUCTION), phrase(std::move(instr)), context(std::move(c)) {}

    std::string Command::toString(int depth) {
        std::string text_rep;
        if (std::holds_alternative<std::unique_ptr<Instruction>>(phrase))
            text_rep += std::get<std::unique_ptr<Instruction>>(phrase)->toString(depth);
        else
            text_rep += std::get<std::unique_ptr<FuncDef>>(phrase)->toString(depth);
        return text_rep;
    }

    void Command::execute() {
        if (type == INSTRUCTION)
            std::get<std::unique_ptr<Instruction>>(phrase)->execute();
        else {
            std::unique_ptr<FuncDef> f_def = std::move(std::get<std::unique_ptr<FuncDef>>(phrase));
            context->saveFuncDef(f_def->func_name, f_def->params, f_def->func_body);
        }
    }
}