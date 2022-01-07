#ifndef JEZYK_Z_CZASEM_FUNCARGSNODE_H
#define JEZYK_Z_CZASEM_FUNCARGSNODE_H

#include "astNode.h"

namespace parser {
    class FuncArgsNode : public ASTNode {
    public:
        FuncArgsNode(ASTNode *parent) : ASTNode(parent) {}

        std::string getTextRepresentation(int depth) override {
            return getUsualTextRepresentation(depth, "Function Arguments\n");
        }
    };
}

#endif //JEZYK_Z_CZASEM_FUNCARGSNODE_H
