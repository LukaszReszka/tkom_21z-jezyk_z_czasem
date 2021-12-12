#ifndef JEZYK_Z_CZASEM_SHOWFUNCNODE_H
#define JEZYK_Z_CZASEM_SHOWFUNCNODE_H

#include "astNode.h"

namespace parser {
    class ShowFuncNode : public ASTNode {
    public:
        ShowFuncNode(ASTNode *parent) : ASTNode(parent) {}

        std::string getTextRepresentation(int depth) override {
            return getUsualTextRepresentation(depth, "SHOW Function\n");
        }
        
    };
}


#endif //JEZYK_Z_CZASEM_SHOWFUNCNODE_H
