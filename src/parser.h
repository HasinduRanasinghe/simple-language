#pragma once
#include <vector>
#include <memory>
#include "token.h"
#include "ast.h"

class Parser {
private:
    std::vector<Token> tokens;
    size_t current_pos;

    Token current_token();
    void advance();
    std::unique_ptr<ASTNode> factor();
    std::unique_ptr<ASTNode> term();
    std::unique_ptr<ASTNode> expr();

public:
    Parser(const std::vector<Token>& t);
    std::unique_ptr<ASTNode> parse();
};