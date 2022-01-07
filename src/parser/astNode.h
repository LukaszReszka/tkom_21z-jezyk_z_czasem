#ifndef JEZYK_Z_CZASEM_ASTNODE_H
#define JEZYK_Z_CZASEM_ASTNODE_H

#include <vector>

namespace parser {
    class ASTNode {
    public:
        ASTNode(ASTNode *node) : parent_node(node) {}

        virtual ~ASTNode() {
            for (auto child: children_nodes)
                delete child;

            delete this;
        };

        virtual std::string getTextRepresentation(int depth) = 0;

        std::string getUsualTextRepresentation(int depth, std::string header) {
            std::string res = "";
            for (int i = 0; i < depth; ++i)
                res += "-";
            res += header;
            for (auto node: children_nodes)
                res += node->getTextRepresentation(depth + 1);
            return res;
        }

        std::vector<ASTNode *> children_nodes;
        ASTNode *parent_node;
    };
}
#endif //JEZYK_Z_CZASEM_ASTNODE_H
