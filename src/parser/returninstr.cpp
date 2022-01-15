#include <memory>
#include "returninstr.h"

namespace parser {
    ReturnInstr::ReturnInstr(std::unique_ptr<Expression> ret_val) : returned_value(std::move(ret_val)) {}

    std::string ReturnInstr::toString(int depth) {
        std::string hyphens;
        for (int i = 0; i < depth; ++i)
            hyphens += "-";
        std::string text_rep = hyphens + "RET\n" + returned_value->toString(depth + 1);

        return text_rep;
    }

    void ReturnInstr::execute(std::shared_ptr<interpreter::Context> cont) {

    }
}