#include "parser.h"
#include <stdexcept>

/**
 * @brief Constructs a Parser object with a sequence of tokens.
 *        Initializes the current position to the start of the token list.
 * 
 * @param t The vector of tokens to be parsed.
 */
Parser::Parser(const std::vector<Token>& t) : tokens(t), current_pos(0) {}

/**
 * @brief Retrieves the current token from the token list.
 *        Returns EOF_TOKEN if the end of the list is reached.
 * 
 * @return Token The current token.
 */
Token Parser::current_token() {
    if (current_pos < tokens.size()) {
        return tokens[current_pos];
    }
    return Token(EOF_TOKEN, "");
}

/**
 * @brief Advances the current position to the next token in the list.
 */
void Parser::advance() {
    current_pos++;
}

/**
 * @brief Parses a factor from the token list.
 *        Handles numbers, identifiers (variables and assignments), and parenthesized expressions.
 * 
 * @return std::unique_ptr<ASTNode> The parsed AST node representing the factor.
 * 
 * @throws std::runtime_error If an unexpected token is encountered or a closing parenthesis is missing.
 */
std::unique_ptr<ASTNode> Parser::factor() {
    Token token = current_token();
    
    // Handle numeric literals
    if (token.type == NUMBER) {
        advance();
        return std::make_unique<NumberNode>(std::stod(token.value));
    }
    
    // Handle identifiers (variables and assignments)
    if (token.type == IDENTIFIER) {
        std::string var_name = token.value;
        advance();
        
        // If the next token is '=', this is an assignment
        if (current_token().type == EQUALS) {
            advance();
            return std::make_unique<AssignmentNode>(var_name, expr());
        }
        
        // Otherwise, it's a variable reference
        return std::make_unique<VariableNode>(var_name);
    }
    
    // Handle parenthesized expressions
    if (token.type == LPAREN) {
        advance();
        auto node = expr();
        
        if (current_token().type != RPAREN) {
            throw std::runtime_error("Expected ')'");
        }
        advance();
        return node;
    }
    
    // If none of the above, throw an error for unexpected token
    throw std::runtime_error("Unexpected token: " + token.value);
}

/**
 * @brief Parses a term from the token list.
 *        Handles multiplication and division operations.
 * 
 * @return std::unique_ptr<ASTNode> The parsed AST node representing the term.
 */
std::unique_ptr<ASTNode> Parser::term() {
    auto node = factor();
    
    // Handle chained multiplication and division
    while (current_token().type == MULTIPLY || current_token().type == DIVIDE) {
        TokenType op = current_token().type;
        advance();
        node = std::make_unique<BinaryOpNode>(std::move(node), op, factor());
    }
    
    return node;
}

/**
 * @brief Parses an expression from the token list.
 *        Handles addition and subtraction operations.
 * 
 * @return std::unique_ptr<ASTNode> The parsed AST node representing the expression.
 */
std::unique_ptr<ASTNode> Parser::expr() {
    auto node = term();
    
    // Handle chained addition and subtraction
    while (current_token().type == PLUS || current_token().type == MINUS) {
        TokenType op = current_token().type;
        advance();
        node = std::make_unique<BinaryOpNode>(std::move(node), op, term());
    }
    
    return node;
}

/**
 * @brief Parses the entire token sequence and returns the root AST node.
 *        Starts parsing from the highest-level expression.
 * 
 * @return std::unique_ptr<ASTNode> The root node of the parsed AST.
 */
std::unique_ptr<ASTNode> Parser::parse() {
    return expr();
}