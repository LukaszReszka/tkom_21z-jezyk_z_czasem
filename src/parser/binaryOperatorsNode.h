#ifndef JEZYK_Z_CZASEM_BINARYOPERATORSNODE_H
#define JEZYK_Z_CZASEM_BINARYOPERATORSNODE_H

#include "astNode.h"
#include "binaryOperators.h"

namespace parser {
    class BinaryOperatorsNode : public ASTNode {
    public:
        BinaryOperatorsNode(ASTNode *parent) : ASTNode(parent) {}

        int operator_type = NONE;
    };
}

#endif //JEZYK_Z_CZASEM_BINARYOPERATORSNODE_H
