#ifndef JEZYK_Z_CZASEM_IFSTATEMENT_H
#define JEZYK_Z_CZASEM_IFSTATEMENT_H

#include "elifstat.h"

namespace parser {
    class IfStatement : public Phrase {
    public:

        IfStatement(std::unique_ptr<Expression> cond, std::vector<std::unique_ptr<Phrase>> &body,
                    std::vector<std::unique_ptr<ElifStat>> &elifs);

        std::string toString() override;

        void execute() override;

    private:
        std::unique_ptr<Expression> cond;
        std::vector<std::unique_ptr<Phrase>> body;
        std::vector<std::unique_ptr<ElifStat>> elifs;
    };
}


#endif //JEZYK_Z_CZASEM_IFSTATEMENT_H
