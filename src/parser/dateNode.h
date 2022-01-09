#ifndef JEZYK_Z_CZASEM_DATENODE_H
#define JEZYK_Z_CZASEM_DATENODE_H

#include "astNode.h"
#include "../lexer/timeMoment.h"

namespace parser {
    class DateNode : public ASTNode {
    public:
        DateNode(ASTNode *parent) : ASTNode(parent) {}

        lexer::TimeMoment moment;

        std::string getTextRepresentation(int depth) override {
            std::string res = "";
            for (int i = 0; i < depth; ++i)
                res += "-";
            res += "Time moment - date: " + std::to_string(moment.getDay()) + "/" +
                   std::to_string(moment.getMonth()) + "/" + std::to_string(moment.getYear()) + "\n";
            return res;
        }
    };
}

#endif //JEZYK_Z_CZASEM_DATENODE_H
