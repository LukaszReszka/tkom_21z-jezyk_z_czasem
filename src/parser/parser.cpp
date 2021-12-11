#include "parser.h"
#include "returnNode.h"
#include "whileLoopNode.h"
#include "blockNode.h"
#include "ifNode.h"
#include "errorNode.h"
#include "elifNode.h"
#include "elseNode.h"
#include "funcDefNode.h"
#include "identifierNode.h"
#include "funcArgsNode.h"
#include "funcCallNode.h"
#include "assignOperatorNode.h"
#include "showFuncNode.h"
#include "stringNode.h"

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
        FuncDefNode *func_def = new FuncDefNode(program);
        program->children_nodes.push_back(func_def);
        advance();
        parseIdentifier(func_def);
        advance();
        parseFuncArgs(func_def);
        advance();
        parseInstructionsBlock(func_def);
    }

    void Parser::parseInstruction(ASTNode *parent) {

        if (current_token.type == lexer::T_IDENTIFIER)
            parseAssignOperator(parent);
        else if (current_token.type == lexer::T_IF)
            parseIf(parent);
        else if (current_token.type == lexer::T_WHILE)
            parseWhileLoop(parent);
        else if (current_token.type == lexer::T_DOT)
            parseFuncCall(parent);
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

    void Parser::parseAssignOperator(ASTNode *parent) {
        AssignOperatorNode *assign_operation = new AssignOperatorNode(parent);
        parent->children_nodes.push_back(assign_operation);
        parseIdentifier(assign_operation);
        advance();
        if (current_token.type != lexer::T_ASSIGN) {
            assign_operation->children_nodes.clear();
            assign_operation->children_nodes.push_back(new ErrorNode(assign_operation));
            return;
        }
        advance();
        if (current_token.type == lexer::T_DOT)
            parseFuncCall(assign_operation);
        else
            parseArithmeticExpr(assign_operation);
    }

    void Parser::parseShowFunc(ASTNode *parent) {
        ShowFuncNode *show_func = new ShowFuncNode(parent);
        parent->children_nodes.push_back(show_func);
        advance();

        if (current_token.type != lexer::T_PARENTHESES_1) {
            show_func->children_nodes.push_back(new ErrorNode(show_func));
            return;
        }
        advance();
        if (current_token.type == lexer::T_STRING)
            parseString(show_func);
        else
            parseArithmeticExpr(show_func);
        advance();

        while (current_token.type == lexer::T_COMMA) {
            advance();
            if (current_token.type == lexer::T_STRING)
                parseString(show_func);
            else
                parseArithmeticExpr(show_func);
            advance();
        }

        if (current_token.type != lexer::T_PARENTHESES_2) {
            show_func->children_nodes.clear();
            show_func->children_nodes.push_back(new ErrorNode(show_func));
        }
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

    void Parser::parseIdentifier(ASTNode *parent) {
        if (current_token.type == lexer::T_IDENTIFIER) {
            IdentifierNode *id = new IdentifierNode(parent);
            id->identifier = std::get<std::string>(current_token.value);
            parent->children_nodes.push_back(id);
        } else
            parent->children_nodes.push_back(new ErrorNode(parent));
    }

    void Parser::parseFuncArgs(ASTNode *parent) {
        FuncArgsNode *func_args = new FuncArgsNode(parent);
        parent->children_nodes.push_back(func_args);

        if (current_token.type != lexer::T_PARENTHESES_1) {
            func_args->children_nodes.push_back(new ErrorNode(func_args));
            return;
        }
        advance();

        if (current_token.type == lexer::T_IDENTIFIER) {
            parseIdentifier(func_args);
            advance();
            while (current_token.type == lexer::T_COMMA) {
                advance();
                parseIdentifier(func_args);
                advance();
            }
        }

        if (current_token.type != lexer::T_PARENTHESES_2) {
            func_args->children_nodes.clear();
            func_args->children_nodes.push_back(new ErrorNode(func_args));
        }
    }

    void Parser::parseFuncCall(ASTNode *parent) {
        FuncCallNode *func_call = new FuncCallNode(parent);
        parent->children_nodes.push_back(func_call);
        advance();
        parseIdentifier(func_call);
        advance();
        parseFuncArgs(func_call);
    }

    void Parser::parseString(ASTNode *parent) {
        StringNode *string_node = new StringNode(parent);
        parent->children_nodes.push_back(string_node);
        string_node->str = std::get<std::string>(current_token.value);
    }
    
    void Parser::parseCondition(ASTNode *parent) {
        //TODO
    }

    void Parser::parseArithmeticExpr(ASTNode *parent) {
        //TODO
    }
}