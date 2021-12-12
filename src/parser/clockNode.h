#ifndef JEZYK_Z_CZASEM_CLOCKNODE_H
#define JEZYK_Z_CZASEM_CLOCKNODE_H

#include "astNode.h"
#include "../lexer/timeMoment.h"

namespace parser {
    class ClockNode : public ASTNode {
    public:
        ClockNode(ASTNode *parent) : ASTNode(parent) {}

        lexer::TimeMoment moment;
    };
}

#endif //JEZYK_Z_CZASEM_CLOCKNODE_H
