#ifndef JEZYK_Z_CZASEM_BLOCKNODE_H
#define JEZYK_Z_CZASEM_BLOCKNODE_H

#include "astNode.h"

namespace parser {
    class BlockNode : public ASTNode {
    public:
        BlockNode(ASTNode *parent) : ASTNode(parent) {}
    };
}

#endif //JEZYK_Z_CZASEM_BLOCKNODE_H
