#ifndef JEZYK_Z_CZASEM_IFNODE_H
#define JEZYK_Z_CZASEM_IFNODE_H

#include "astNode.h"

namespace parser {
    class IfNode : public ASTNode {
    public:
        IfNode(ASTNode *parent) : ASTNode(parent) {}
    };
}

#endif //JEZYK_Z_CZASEM_IFNODE_H
