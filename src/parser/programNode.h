#ifndef JEZYK_Z_CZASEM_PROGRAMNODE_H
#define JEZYK_Z_CZASEM_PROGRAMNODE_H

#include "astNode.h"

namespace parser {
    class ProgramNode : public ASTNode {
    public:
        ProgramNode() : ASTNode(this) {}
        
    };
}

#endif //JEZYK_Z_CZASEM_PROGRAMNODE_H
