#ifndef JEZYK_Z_CZASEM_BINARYOPERATORSNODE_H
#define JEZYK_Z_CZASEM_BINARYOPERATORSNODE_H

#include "astNode.h"
#include "binaryOperators.h"
#include "expression.h"

namespace parser {
    class BinaryOperatorsNode : public ASTNode {
    public:
        BinaryOperatorsNode(ASTNode *parent) : ASTNode(parent) {}

        int operator_type = NONE;

        std::string getTextRepresentation(int depth) override {
            std::string res = "";
            for (int i = 0; i < depth; ++i)
                res += "-";

            switch (operator_type) {
                case PLUS:
                    res += "PLUS operation\n";
                    break;

                case MINUS:
                    res += "MINUS operation\n";
                    break;

                case MULTIPLY:
                    res += "MULTIPLY operation\n";
                    break;

                case DIVIDE:
                    res += "DIVIDE operation\n";
                    break;

                case OR:
                    res += "OR operation\n";
                    break;

                case AND:
                    res += "AND operation\n";
                    break;

                case EQUAL:
                    res += "EQUAL operation\n";
                    break;

                case NOT_EQUAL:
                    res += "NOT_EQUAL operation\n";
                    break;

                case GREATER:
                    res += "GREATER operation\n";
                    break;

                case GREATER_EQUAL:
                    res += "GREATER_EQUAL operation\n";
                    break;

                case LESS:
                    res += "LESS operation\n";
                    break;

                case LESS_EQUAL:
                    res += "LESS_EQUAL operation\n";
            }

            for (auto node: children_nodes)
                res += node->getTextRepresentation(depth + 1);
            return res;
        }
    };
}

#endif //JEZYK_Z_CZASEM_BINARYOPERATORSNODE_H
