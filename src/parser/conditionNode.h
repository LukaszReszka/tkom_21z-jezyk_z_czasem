#ifndef JEZYK_Z_CZASEM_CONDITIONNODE_H
#define JEZYK_Z_CZASEM_CONDITIONNODE_H

#include "astNode.h"

namespace parser {
    class ConditionNode : public ASTNode {
    public:
        ConditionNode(ASTNode *parent) : ASTNode(parent) {}

        std::string getTextRepresentation(int depth) override {
            return getUsualTextRepresentation(depth, "Condition\n");
        }
    };
}

#endif //JEZYK_Z_CZASEM_CONDITIONNODE_H
