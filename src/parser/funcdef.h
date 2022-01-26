#ifndef JEZYK_Z_CZASEM_FUNCDEF_H
#define JEZYK_Z_CZASEM_FUNCDEF_H

#include "instruction.h"
#include "../interpreter/context.h"

namespace parser {
    class FuncDef : public Phrase {
    public:
        FuncDef(std::string &name, std::vector<std::string> &params, std::vector<std::unique_ptr<Phrase>> &body,
                std::shared_ptr<interpreter::Context> c);

        std::string toString(int depth) override;

        void execute() override;

    private:
        std::string func_name;
        std::vector<std::string> params;
        std::vector<std::unique_ptr<Phrase>> func_body;

        std::shared_ptr<interpreter::Context> context;
    };
}

#endif //JEZYK_Z_CZASEM_FUNCDEF_H
