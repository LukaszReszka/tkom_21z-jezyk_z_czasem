#ifndef JEZYK_Z_CZASEM_FUNCDEFNODE_H
#define JEZYK_Z_CZASEM_FUNCDEFNODE_H

#include "astNode.h"

namespace parser {
    class FuncDefNode : public ASTNode {
    public:
        FuncDefNode(ASTNode *parent) : ASTNode(parent) {}

        std::string getTextRepresentation(int depth) override {
            std::string res = "";
            for (int i = 0; i < depth; ++i)
                res += "-";
            res += "Function Definition\n";
            for (auto node: children_nodes)
                res += node->getTextRepresentation(depth + 1);
            return res;
        }
    };
}


#endif //JEZYK_Z_CZASEM_FUNCDEFNODE_H
