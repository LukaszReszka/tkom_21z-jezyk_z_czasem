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

        //virtual void parse() = 0;

        std::vector<ASTNode *> children_nodes;
        ASTNode *parent_node;
    };
}
#endif //JEZYK_Z_CZASEM_ASTNODE_H
