#ifndef JEZYK_Z_CZASEM_ASSIGNOPERATORNODE_H
#define JEZYK_Z_CZASEM_ASSIGNOPERATORNODE_H

#include "astNode.h"
#include "phrase.h"

namespace parser {
    class AssignOperatorNode : public ASTNode {
    public:
        AssignOperatorNode(ASTNode *parent) : ASTNode(parent) {}

        std::string getTextRepresentation(int depth) override {
            std::string res = "", is_assigned_with = "";
            for (int i = 0; i < depth; ++i) {
                res += "-";
                is_assigned_with += "-";
            }
            res += "Assign Operation\n";
            is_assigned_with += "is assigned to\n";

            for (int j = 0; j < children_nodes.size(); ++j) {
                if (j == 1)
                    res += is_assigned_with;
                res += children_nodes[j]->getTextRepresentation(depth + 1);
            }
            return res;
        }
    };
}

#endif //JEZYK_Z_CZASEM_ASSIGNOPERATORNODE_H
