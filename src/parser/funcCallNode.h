#ifndef JEZYK_Z_CZASEM_FUNCCALLNODE_H
#define JEZYK_Z_CZASEM_FUNCCALLNODE_H

#include "astNode.h"

namespace parser {
    class FuncCallNode : public ASTNode {
    public:
        FuncCallNode(ASTNode *parent) : ASTNode(parent) {}

        std::string getTextRepresentation(int depth) override {
            return getUsualTextRepresentation(depth, "Function Call\n");
        }
    };
}

#endif //JEZYK_Z_CZASEM_FUNCCALLNODE_H
