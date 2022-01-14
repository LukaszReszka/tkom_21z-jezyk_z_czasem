#ifndef JEZYK_Z_CZASEM_ELIFSTAT_H
#define JEZYK_Z_CZASEM_ELIFSTAT_H

#include "phrase.h"
#include "expression.h"
#include <memory>
#include <string>
#include <vector>

namespace parser {
    class ElifStat : public Phrase {
    public:

        ElifStat(std::unique_ptr<Expression> cond, std::vector<std::unique_ptr<Phrase>> &body);

        std::string toString() override;

        void execute() override;

    private:
        std::unique_ptr<Expression> cond;
        std::vector<std::unique_ptr<Phrase>> body;
    };
}


#endif //JEZYK_Z_CZASEM_ELIFSTAT_H
