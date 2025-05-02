#include "ast.h"
#include <stdexcept>

// NumberNode represents a numeric literal in the Abstract Syntax Tree (AST).
NumberNode::NumberNode(double val) : value(val) {}

/**
 * @brief Evaluates the numeric literal represented by this node.
 * 
 * @param variables A map containing variable names as keys and their corresponding values.
 *                  This parameter is unused in this method since numeric literals do not depend on variables.
 * 
 * @return The numeric value stored in this node.
 */
double NumberNode::evaluate(std::map<std::string, double>& variables) {
    return value;
}

// BinaryOpNode represents a binary operation in the AST.
BinaryOpNode::BinaryOpNode(std::unique_ptr<ASTNode> l, TokenType o, std::unique_ptr<ASTNode> r)
    : left(std::move(l)), op(o), right(std::move(r)) {}

/**
 * @brief Evaluates the binary operation represented by this node.
 *        It computes the result of applying the operator to the left and right operands.
 * 
 * @param variables A map containing variable names as keys and their corresponding values.
 *                  This is used to evaluate any variable references in the expression.
 * 
 * @return The result of the binary operation as a double.
 * 
 * @throws std::runtime_error If the operator is unknown or if a division by zero is attempted.
 */
double BinaryOpNode::evaluate(std::map<std::string, double>& variables) {
    double left_val = left->evaluate(variables);
    double right_val = right->evaluate(variables);

    // Perform the operation based on the operator type.
    switch (op) {
        case PLUS: 
            return left_val + right_val;
        case MINUS: 
            return left_val - right_val;
        case MULTIPLY: 
            return left_val * right_val;
        case DIVIDE: 
            if (right_val == 0) {
                throw std::runtime_error("Division by zero");
            }
            return left_val / right_val;
        default: 
            throw std::runtime_error("Unknown operator");
    }
}

// VariableNode represents a variable in the AST.
VariableNode::VariableNode(const std::string& n) : name(n) {}

/**
 * @brief Evaluates the variable represented by this node.
 *        It retrieves the value of the variable from the provided variable map.
 * 
 * @param variables A map containing variable names as keys and their corresponding values.
 * 
 * @return The value of the variable as a double.
 * 
 * @throws std::runtime_error If the variable is not defined in the map.
 */
double VariableNode::evaluate(std::map<std::string, double>& variables) {
    auto it = variables.find(name);
    if (it == variables.end()) {
        throw std::runtime_error("Undefined variable: " + name);
    }
    return variables[name];
}

// AssignmentNode represents an assignment operation in the AST.
AssignmentNode::AssignmentNode(const std::string& var, std::unique_ptr<ASTNode> val)
    : variable(var), value(std::move(val)) {}

/**
 * @brief Evaluates the assignment operation represented by this node.
 *        It computes the value of the right-hand side expression and assigns it to the variable.
 * 
 * @param variables A map containing variable names as keys and their corresponding values.
 *                  The result of the assignment is stored in this map.
 * 
 * @return The value assigned to the variable as a double.
 */
double AssignmentNode::evaluate(std::map<std::string, double>& variables) {
    double result = value->evaluate(variables);
    variables[variable] = result;
    return result;