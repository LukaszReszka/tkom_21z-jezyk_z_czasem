#include <memory>
#include <utility>
#include "returninstr.h"

namespace parser {
    ReturnInstr::ReturnInstr(std::unique_ptr<Expression> ret_val, std::shared_ptr<interpreter::Context> c)
            : returned_value(std::move(ret_val)), context(std::move(c)) {}

    std::string ReturnInstr::toString(int depth) {
        std::string hyphens;
        for (int i = 0; i < depth; ++i)
            hyphens += "-";
        std::string text_rep = hyphens + "RET\n" + returned_value->toString(depth + 1);

        return text_rep;
    }

    void ReturnInstr::execute() {
        context->endProgramExecution = true;
        context->returned_value = returned_value->evaluate();
    }
}