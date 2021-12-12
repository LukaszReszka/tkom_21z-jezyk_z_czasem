#ifndef JEZYK_Z_CZASEM_TIMESTAMPNODE_H
#define JEZYK_Z_CZASEM_TIMESTAMPNODE_H

#include "astNode.h"
#include "../lexer/timeMoment.h"

namespace parser {
    class TimestampNode : public ASTNode {
    public:
        TimestampNode(ASTNode *parent) : ASTNode(parent) {}

        lexer::TimeMoment moment;
    };
}


#endif //JEZYK_Z_CZASEM_TIMESTAMPNODE_H
