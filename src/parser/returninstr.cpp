#include <memory>
#include "returninstr.h"

namespace parser {
    ReturnInstr::ReturnInstr(std::unique_ptr<Expression> ret_val) : returned_value(std::move(ret_val)) {}

    std::string ReturnInstr::toString() {
        return std::string();
    }

    void ReturnInstr::execute() {

    }
}