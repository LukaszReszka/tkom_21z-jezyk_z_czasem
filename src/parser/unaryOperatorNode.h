#ifndef JEZYK_Z_CZASEM_UNARYOPERATORNODE_H
#define JEZYK_Z_CZASEM_UNARYOPERATORNODE_H

#include "astNode.h"
#include "unaryOperators.h"

namespace parser {
    class UnaryOperatorNode : public ASTNode {
    public:
        UnaryOperatorNode(ASTNode *parent) : ASTNode(parent) {}

        int operator_type = NEGATION;

        std::string getTextRepresentation(int depth) override {
            std::string res = "";
            for (int i = 0; i < depth; ++i)
                res += "-";

            switch (operator_type) {
                case NEGATION:
                    res += "Arithmetic NEGATION\n";
                    break;

                case SEC:
                    res += "Convert to SECONDS\n";
                    break;

                case MIN:
                    res += "Convert to MINUTES\n";
                    break;

                case HOUR:
                    res += "Convert to HOURS\n";
            }
            res += children_nodes[0]->getTextRepresentation(depth + 1);
            return res;
        }
    };
}
#endif //JEZYK_Z_CZASEM_UNARYOPERATORNODE_H
