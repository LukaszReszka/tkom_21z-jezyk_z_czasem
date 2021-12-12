#ifndef JEZYK_Z_CZASEM_CLOCKNODE_H
#define JEZYK_Z_CZASEM_CLOCKNODE_H

#include "astNode.h"
#include "../lexer/timeMoment.h"

namespace parser {
    class ClockNode : public ASTNode {
    public:
        ClockNode(ASTNode *parent) : ASTNode(parent) {}

        lexer::TimeMoment moment;

        std::string getTextRepresentation(int depth) override {
            std::string res = "";
            for (int i = 0; i < depth; ++i)
                res += "-";
            res += "Time moment - clock: " + std::to_string(moment.getHour()) + ":" + std::to_string(moment.getMin()) +
                   ":" + std::to_string(moment.getSec()) + "\n";
            return res;
        }
    };
}

#endif //JEZYK_Z_CZASEM_CLOCKNODE_H
