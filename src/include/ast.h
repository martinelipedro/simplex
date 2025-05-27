#ifndef SIMPLEX_AST_H
#define SIMPLEX_AST_H

#include <memory>
#include <utility>
#include "lexer.h"

struct ASTNode
{
    virtual ~ASTNode();
    virtual void print(int level = 0) const {}
};

struct ASTCompound : public ASTNode
{
    std::vector<ASTNode *> children;
    inline void addChild(ASTNode *child) { this->children.push_back(child); }
};

struct NumberNode : public ASTNode
{
    double value;
    explicit NumberNode(double val) : value(val) {}

    void print(int level = 0) const override
    {
        for (int i = 0; i < level; ++i)
            std::cout << "   ";

        std::cout << "NumberNode(value: " << value << ")\n";
    }
};

struct BinaryOpNode : public ASTNode
{
    ASTNode *left;
    TokenType op;
    ASTNode *right;

    BinaryOpNode(ASTNode *l, TokenType op, ASTNode *r) : left(l), op(op), right(r) {};

    void print(int level = 0) const override
    {
        for (int i = 0; i < level; ++i)
            std::cout << "   ";

        printf("BinaryOpNode(operator: %d)\n", static_cast<int>(op));
        if (left)
            left->print(level + 1);
        if (right)
            right->print(level + 1);
    }
};

struct FunctionCallNode : public ASTNode
{
    ASTNode *expression;

    explicit FunctionCallNode(ASTNode *expr) : expression(expr) {}

    void print(int level = 0) const override
    {
        for (int i = 0; i < level; ++i)
            std::cout << "   ";
    }
};

#endif
