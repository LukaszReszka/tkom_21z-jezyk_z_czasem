#ifndef JEZYK_Z_CZASEM_WHILELOOPNODE_H
#define JEZYK_Z_CZASEM_WHILELOOPNODE_H

#include "astNode.h"

namespace parser {
    class WhileLoopNode : public ASTNode {
    public:
        WhileLoopNode(ASTNode *parent) : ASTNode(parent) {}
    };
}

#endif //JEZYK_Z_CZASEM_WHILELOOPNODE_H
