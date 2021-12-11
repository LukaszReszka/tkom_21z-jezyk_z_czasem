#ifndef JEZYK_Z_CZASEM_IDENTIFIERNODE_H
#define JEZYK_Z_CZASEM_IDENTIFIERNODE_H

#include <string>
#include "astNode.h"

namespace parser {
    class IdentifierNode : public ASTNode {
    public:
        IdentifierNode(ASTNode *parent) : ASTNode(parent) {}

        std::string identifier;
    };
}
#endif //JEZYK_Z_CZASEM_IDENTIFIERNODE_H
