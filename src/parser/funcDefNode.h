#ifndef JEZYK_Z_CZASEM_FUNCDEFNODE_H
#define JEZYK_Z_CZASEM_FUNCDEFNODE_H

#include "astNode.h"

namespace parser {
    class FuncDefNode : public ASTNode {
    public:
        FuncDefNode(ASTNode *parent) : ASTNode(parent) {}

    };
}


#endif //JEZYK_Z_CZASEM_FUNCDEFNODE_H
