#include "parser.h"
#include "returnNode.h"
#include "whileLoopNode.h"
#include "blockNode.h"
#include "ifNode.h"
#include "errorNode.h"
#include "elifNode.h"
#include "elseNode.h"

using lexer::Token;

namespace parser {

    void Parser::parseProgram() {
        advance();

        while (current_token.type != lexer::T_END) {
            if (current_token.type == lexer::T_FUNC)
                parseFuncDef();
            else
                parseInstruction(program);

            advance();
        }
    }

    void Parser::parseFuncDef() {
        //TODO
    }

    void Parser::parseInstruction(ASTNode *parent) {

        if (current_token.type == lexer::T_IDENTIFIER)
            parseAssignOrFuncCall(parent);
        else if (current_token.type == lexer::T_IF)
            parseIf(parent);
        else if (current_token.type == lexer::T_WHILE)
            parseWhileLoop(parent);
        else if (current_token.type == lexer::T_RET)
            parseRet(parent);
        else if (current_token.type == lexer::T_SHOW)
            parseShowFunc(parent);
        else
            parent->children_nodes.push_back(new ErrorNode(parent));
    }

    void Parser::parseRet(ASTNode *parent) {
        ReturnNode *ret = new ReturnNode(parent);
        parent->children_nodes.push_back(ret);
        advance();
        if (current_token.type != lexer::T_PARENTHESES_1) {
            ret->children_nodes.push_back(new ErrorNode(ret));
            return;
        }
        advance();
        parseArithmeticExpr(ret);
        advance();
        if (current_token.type != lexer::T_PARENTHESES_2) {
            ret->children_nodes.clear();
            ret->children_nodes.push_back(new ErrorNode(ret));
            return;
        }
        advance();
        if (current_token.type != lexer::T_SEMICOLON) {
            ret->children_nodes.clear();
            ret->children_nodes.push_back(new ErrorNode(ret));
            return;
        }
    }

    void Parser::parseIf(ASTNode *parent) {
        IfNode *if_statement = new IfNode(parent);
        parent->children_nodes.push_back(if_statement);
        advance();
        parseCondition(if_statement);
        advance();
        parseInstructionsBlock(if_statement);
        advance();
        while (current_token.type == lexer::T_ELIF) {
            parseElif(if_statement);
            advance();
        }

        if (current_token.type == lexer::T_ELSE) {
            parseElse(if_statement);
        }
    }

    void Parser::parseWhileLoop(ASTNode *parent) {
        WhileLoopNode *while_loop = new WhileLoopNode(parent);
        parent->children_nodes.push_back(while_loop);
        advance();
        parseCondition(while_loop);
        advance();
        parseInstructionsBlock(while_loop);
    }

    void Parser::parseAssignOrFuncCall(ASTNode *parent) {
        //TODO
    }

    void Parser::parseShowFunc(ASTNode *parent) {
        //TODO
    }

    void Parser::parseArithmeticExpr(ASTNode *parent) {
        //TODO
    }

    void Parser::parseCondition(ASTNode *parent) {
        //TODO
    }

    void Parser::parseInstructionsBlock(ASTNode *parent) {
        BlockNode *block = new BlockNode(parent);
        parent->children_nodes.push_back(block);
        if (current_token.type != lexer::T_BRACE_1) {
            block->children_nodes.push_back(new ErrorNode(block));
            return;
        }
        advance();
        while (current_token.type != lexer::T_END && current_token.type != lexer::T_BRACE_2) {
            parseInstruction(block);
            advance();
        }

        if (current_token.type != lexer::T_BRACE_2) {
            block->children_nodes.clear();
            block->children_nodes.push_back(new ErrorNode(block));
            return;
        }
    }

    void Parser::parseElif(ASTNode *parent) {
        ElifNode *elif_statement = new ElifNode(parent);
        parent->children_nodes.push_back(elif_statement);
        advance();
        parseCondition(elif_statement);
        advance();
        parseInstructionsBlock(elif_statement);
    }

    void Parser::parseElse(ASTNode *parent) {
        ElseNode *else_statement = new ElseNode(parent);
        parent->children_nodes.push_back(else_statement);
        advance();
        parseInstructionsBlock(else_statement);
    }
}