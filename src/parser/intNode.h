#ifndef JEZYK_Z_CZASEM_INTNODE_H
#define JEZYK_Z_CZASEM_INTNODE_H

#include "astNode.h"

namespace parser {
    class IntNode : public ASTNode {
    public:
        IntNode(ASTNode *parent) : ASTNode(parent) {}

        int value;

        std::string getTextRepresentation(int depth) override {
            std::string res = "";
            for (int i = 0; i < depth; ++i)
                res += "-";
            res += "INT: " + std::to_string(value) + "\n";
            return res;
        }
    };
}


#endif //JEZYK_Z_CZASEM_INTNODE_H
