#pragma once
#include <memory>
#include <string>
#include <map>
#include "token.h"

// Base class for all AST nodes
class ASTNode {
public:
    virtual ~ASTNode() = default;
    virtual double evaluate(std::map<std::string, double>& variables) = 0;
};

// Represents a numeric literal
class NumberNode : public ASTNode {
private:
    double value;

public:
    NumberNode(double val);
    double evaluate(std::map<std::string, double>& variables) override;
};

// Represents a binary operation
class BinaryOpNode : public ASTNode {
private:
    std::unique_ptr<ASTNode> left;
    TokenType op;
    std::unique_ptr<ASTNode> right;

public:
    BinaryOpNode(std::unique_ptr<ASTNode> l, TokenType o, std::unique_ptr<ASTNode> r);
    double evaluate(std::map<std::string, double>& variables) override;
};

// Represents a variable
class VariableNode : public ASTNode {
private:
    std::string name;

public:
    VariableNode(const std::string& n);
    double evaluate(std::map<std::string, double>& variables) override;
};

// Represents an assignment operation
class AssignmentNode : public ASTNode {
private:
    std::string variable;
    std::unique_ptr<ASTNode> value;

public:
    AssignmentNode(const std::string& var, std::unique_ptr<ASTNode> val);
    double evaluate(std::map<std::string, double>& variables) override;
};