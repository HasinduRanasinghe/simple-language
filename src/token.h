#pragma once
#include <string>

enum TokenType {
    NUMBER,
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    LPAREN,
    RPAREN,
    IDENTIFIER,
    EQUALS,
    EOF_TOKEN
};

struct Token {
    TokenType type;
    std::string value;
    
    Token(TokenType t, const std::string& v) : type(t), value(v) {}
};