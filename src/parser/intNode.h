#ifndef JEZYK_Z_CZASEM_INTNODE_H
#define JEZYK_Z_CZASEM_INTNODE_H

#include "astNode.h"

namespace parser {
    class IntNode : public ASTNode {
    public:
        IntNode(ASTNode *parent) : ASTNode(parent) {}

        int value;
    };
}


#endif //JEZYK_Z_CZASEM_INTNODE_H
