#ifndef JEZYK_Z_CZASEM_TIMEPERIODNODE_H
#define JEZYK_Z_CZASEM_TIMEPERIODNODE_H

#include "astNode.h"
#include "../lexer/timePeriod.h"

namespace parser {
    class TimePeriodNode : public ASTNode {
    public:
        TimePeriodNode(ASTNode *parent) : ASTNode(parent) {}

        lexer::TimePeriod period;

        std::string getTextRepresentation(int depth) override {
            std::string res = "";
            for (int i = 0; i < depth; ++i)
                res += "-";
            res += "Time period: " + std::to_string(std::chrono::duration<int>(period.h).count() / 3600) + " h "
                   + std::to_string(std::chrono::duration<int>(period.m).count() / 60) + " m " +
                   std::to_string(std::chrono::duration<int>(period.s).count()) + " s\n";
            return res;
        }
    };
}


#endif //JEZYK_Z_CZASEM_TIMEPERIODNODE_H
