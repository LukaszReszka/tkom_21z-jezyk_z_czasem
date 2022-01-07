#ifndef JEZYK_Z_CZASEM_ELSENODE_H
#define JEZYK_Z_CZASEM_ELSENODE_H

#include "astNode.h"

namespace parser {
    class ElseNode : public ASTNode {
    public:
        ElseNode(ASTNode *parent) : ASTNode(parent) {}

        std::string getTextRepresentation(int depth) override {
            return getUsualTextRepresentation(depth, "ELSE statement\n");
        }

    };
}

#endif //JEZYK_Z_CZASEM_ELSENODE_H
