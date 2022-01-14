#ifndef JEZYK_Z_CZASEM_FUNCDEF_H
#define JEZYK_Z_CZASEM_FUNCDEF_H

#include "phrase.h"
#include "instruction.h"
#include <string>
#include <vector>
#include <memory>

namespace parser {
    class FuncDef : public Phrase {
    public:
        FuncDef(std::string &name, std::vector<std::string> &params, std::vector<std::unique_ptr<Phrase>> &body);

        std::string toString() override;

        void execute() override;

    private:
        std::string func_name;
        std::vector<std::string> params;
        std::vector<std::unique_ptr<Phrase>> func_body;
    };
}

#endif //JEZYK_Z_CZASEM_FUNCDEF_H
