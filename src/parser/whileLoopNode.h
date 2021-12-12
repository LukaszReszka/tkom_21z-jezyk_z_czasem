#ifndef JEZYK_Z_CZASEM_WHILELOOPNODE_H
#define JEZYK_Z_CZASEM_WHILELOOPNODE_H

#include "astNode.h"

namespace parser {
    class WhileLoopNode : public ASTNode {
    public:
        WhileLoopNode(ASTNode *parent) : ASTNode(parent) {}

        std::string getTextRepresentation(int depth) override {
            return getUsualTextRepresentation(depth, "WHILE loop\n");
        }

    };
}

#endif //JEZYK_Z_CZASEM_WHILELOOPNODE_H
