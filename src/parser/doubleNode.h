#ifndef JEZYK_Z_CZASEM_DOUBLENODE_H
#define JEZYK_Z_CZASEM_DOUBLENODE_H

#include "astNode.h"

namespace parser {
    class DoubleNode : public ASTNode {
    public:
        DoubleNode(ASTNode *parent) : ASTNode(parent) {}

        double value;
    };
}

#endif //JEZYK_Z_CZASEM_DOUBLENODE_H
