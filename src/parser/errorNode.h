#ifndef JEZYK_Z_CZASEM_ERRORNODE_H
#define JEZYK_Z_CZASEM_ERRORNODE_H

#include "astNode.h"

namespace parser {
    class ErrorNode : public ASTNode {
    public:
        ErrorNode(ASTNode *parent) : ASTNode(parent) {}
    };
}

#endif //JEZYK_Z_CZASEM_ERRORNODE_H
