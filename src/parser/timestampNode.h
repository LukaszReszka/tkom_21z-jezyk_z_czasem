#ifndef JEZYK_Z_CZASEM_TIMESTAMPNODE_H
#define JEZYK_Z_CZASEM_TIMESTAMPNODE_H

#include "astNode.h"
#include "../lexer/timeMoment.h"

namespace parser {
    class TimestampNode : public ASTNode {
    public:
        TimestampNode(ASTNode *parent) : ASTNode(parent) {}

        lexer::TimeMoment moment;

        std::string getTextRepresentation(int depth) override {
            std::string res = "";
            for (int i = 0; i < depth; ++i)
                res += "-";
            res += "Time moment - timestamp: " + std::to_string(moment.getDay()) + "/" +
                   std::to_string(moment.getMonth()) + "/" + std::to_string(moment.getYear()) + " " +
                   std::to_string(moment.getHour()) + ":" + std::to_string(moment.getMin()) +
                   ":" + std::to_string(moment.getSec()) + "\n";
            return res;
        }

    };
}


#endif //JEZYK_Z_CZASEM_TIMESTAMPNODE_H
