#ifndef JEZYK_Z_CZASEM_ELIFNODE_H
#define JEZYK_Z_CZASEM_ELIFNODE_H

#include "astNode.h"

namespace parser {
    class ElifNode : public ASTNode {
    public:
        ElifNode(ASTNode *parent) : ASTNode(parent) {}
    };
}

#endif //JEZYK_Z_CZASEM_ELIFNODE_H
