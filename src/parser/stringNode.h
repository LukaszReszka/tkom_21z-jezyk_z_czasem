#ifndef JEZYK_Z_CZASEM_STRINGNODE_H
#define JEZYK_Z_CZASEM_STRINGNODE_H

#include <string>
#include "astNode.h"

namespace parser {
    class StringNode : public ASTNode {
    public:
        StringNode(ASTNode *parent) : ASTNode(parent) {}

        std::string str;
    };
}


#endif //JEZYK_Z_CZASEM_STRINGNODE_H
