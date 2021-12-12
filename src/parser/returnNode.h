#ifndef JEZYK_Z_CZASEM_RETURNNODE_H
#define JEZYK_Z_CZASEM_RETURNNODE_H

#include "astNode.h"

namespace parser {
    class ReturnNode : public ASTNode {
    public:
        ReturnNode(ASTNode *parent) : ASTNode(parent) {}

        std::string getTextRepresentation(int depth) override {
            return getUsualTextRepresentation(depth, "RETURN\n");
        }
    };
}
#endif //JEZYK_Z_CZASEM_RETURNNODE_H
