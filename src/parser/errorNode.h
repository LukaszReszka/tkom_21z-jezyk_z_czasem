#ifndef JEZYK_Z_CZASEM_ERRORNODE_H
#define JEZYK_Z_CZASEM_ERRORNODE_H

#include "astNode.h"

namespace parser {
    class ErrorNode : public ASTNode {
    public:
        ErrorNode(ASTNode *parent, std::string msg) : ASTNode(parent), error_msg(msg) {}

        std::string error_msg;

        std::string getTextRepresentation(int depth) override {
            std::string res = "";
            for (int i = 0; i < depth; ++i)
                res += "-";
            res += "ERROR - " + error_msg + "\n";
            return res;
        }
    };
}

#endif //JEZYK_Z_CZASEM_ERRORNODE_H
