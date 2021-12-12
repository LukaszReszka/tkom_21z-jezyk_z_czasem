#ifndef JEZYK_Z_CZASEM_STRINGNODE_H
#define JEZYK_Z_CZASEM_STRINGNODE_H

#include <string>
#include "astNode.h"

namespace parser {
    class StringNode : public ASTNode {
    public:
        StringNode(ASTNode *parent) : ASTNode(parent) {}

        std::string str;

        std::string getTextRepresentation(int depth) override {
            std::string res = "";
            for (int i = 0; i < depth; ++i)
                res += "-";
            res += "STRING: " + str + "\n";
            return res;
        }
    };
}


#endif //JEZYK_Z_CZASEM_STRINGNODE_H
