#ifndef JEZYK_Z_CZASEM_DOUBLENODE_H
#define JEZYK_Z_CZASEM_DOUBLENODE_H

#include "astNode.h"

namespace parser {
    class DoubleNode : public ASTNode {
    public:
        DoubleNode(ASTNode *parent) : ASTNode(parent) {}

        double value;

        std::string getTextRepresentation(int depth) override {
            std::string res = "";
            for (int i = 0; i < depth; ++i)
                res += "-";
            res += "DOUBLE: " + std::to_string(value) + "\n";
            return res;
        }
    };
}

#endif //JEZYK_Z_CZASEM_DOUBLENODE_H
