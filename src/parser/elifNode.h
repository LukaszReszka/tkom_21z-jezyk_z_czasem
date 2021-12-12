#ifndef JEZYK_Z_CZASEM_ELIFNODE_H
#define JEZYK_Z_CZASEM_ELIFNODE_H

#include "astNode.h"

namespace parser {
    class ElifNode : public ASTNode {
    public:
        ElifNode(ASTNode *parent) : ASTNode(parent) {}

        std::string getTextRepresentation(int depth) override {
            return getUsualTextRepresentation(depth, "ELIF statement\n");
        }
    };
}

#endif //JEZYK_Z_CZASEM_ELIFNODE_H
