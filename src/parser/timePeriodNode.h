#ifndef JEZYK_Z_CZASEM_TIMEPERIODNODE_H
#define JEZYK_Z_CZASEM_TIMEPERIODNODE_H

#include "astNode.h"
#include "../lexer/timePeriod.h"

namespace parser {
    class TimePeriodNode : public ASTNode {
    public:
        TimePeriodNode(ASTNode *parent) : ASTNode(parent) {}

        lexer::TimePeriod period;
    };
}


#endif //JEZYK_Z_CZASEM_TIMEPERIODNODE_H
