#ifndef JEZYK_Z_CZASEM_FUNCARGSNODE_H
#define JEZYK_Z_CZASEM_FUNCARGSNODE_H

#include "astNode.h"

namespace parser {
    class FuncArgsNode : public ASTNode {
    public:
        FuncArgsNode(ASTNode *parent) : ASTNode(parent) {}
    };
}

#endif //JEZYK_Z_CZASEM_FUNCARGSNODE_H
