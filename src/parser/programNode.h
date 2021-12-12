#ifndef JEZYK_Z_CZASEM_PROGRAMNODE_H
#define JEZYK_Z_CZASEM_PROGRAMNODE_H

#include "astNode.h"

namespace parser {
    class ProgramNode : public ASTNode {
    public:
        ProgramNode() : ASTNode(this) {}

        std::string getTextRepresentation(int depth) override {
            std::string res = "PROGRAM ROOT\n";
            for (auto node: children_nodes)
                res += node->getTextRepresentation(1);
            return res;
        }
    };
}

#endif //JEZYK_Z_CZASEM_PROGRAMNODE_H
