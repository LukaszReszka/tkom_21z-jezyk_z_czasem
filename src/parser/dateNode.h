#ifndef JEZYK_Z_CZASEM_DATENODE_H
#define JEZYK_Z_CZASEM_DATENODE_H

#include "astNode.h"
#include "../lexer/timeMoment.h"

namespace parser {
    class DateNode : public ASTNode {
    public:
        DateNode(ASTNode *parent) : ASTNode(parent) {}

        lexer::TimeMoment moment;
    };
}

#endif //JEZYK_Z_CZASEM_DATENODE_H
