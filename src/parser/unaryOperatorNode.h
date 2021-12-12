#ifndef JEZYK_Z_CZASEM_UNARYOPERATORNODE_H
#define JEZYK_Z_CZASEM_UNARYOPERATORNODE_H

#include "astNode.h"
#include "unaryOperators.h"

namespace parser {
    class UnaryOperatorNode : public ASTNode {
    public:
        UnaryOperatorNode(ASTNode *parent) : ASTNode(parent) {}

        int operator_type = NEGATIVE;
    };
}
#endif //JEZYK_Z_CZASEM_UNARYOPERATORNODE_H
