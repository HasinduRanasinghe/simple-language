#pragma once
#include <string>
#include <vector>
#include "token.h"

class Lexer {
private:
    std::string input;
    size_t position;
    char current_char;

    void advance();
    void skip_whitespace();
    Token get_number();
    Token get_identifier();

public:
    Lexer(const std::string& text);
    Token get_next_token();
    std::vector<Token> tokenize();
};