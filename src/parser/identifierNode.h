#ifndef JEZYK_Z_CZASEM_IDENTIFIERNODE_H
#define JEZYK_Z_CZASEM_IDENTIFIERNODE_H

#include <string>
#include "astNode.h"

namespace parser {
    class IdentifierNode : public ASTNode {
    public:
        IdentifierNode(ASTNode *parent) : ASTNode(parent) {}

        std::string identifier;

        std::string getTextRepresentation(int depth) override {
            std::string res = "";
            for (int i = 0; i < depth; ++i)
                res += "-";
            res += "Identifier: " + identifier + "\n";
            return res;
        }
    };
}
#endif //JEZYK_Z_CZASEM_IDENTIFIERNODE_H
