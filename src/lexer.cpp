#include "lexer.h"
#include <cctype>
#include <iostream>

/**
 * @brief Constructs a Lexer object with the given input text.
 *        Initializes the current character to the first character of the input.
 * 
 * @param text The input string to be tokenized.
 */
Lexer::Lexer(const std::string& text) : input(text), position(0) {
    if (!input.empty()) {
        current_char = input[0];
    } else {
        current_char = '\0';
    }
}

/**
 * @brief Advances the position in the input string by one character.
 *        Updates the current character or sets it to '\0' if the end of input is reached.
 */
void Lexer::advance() {
    position++;
    if (position < input.length()) {
        current_char = input[position];
    } else {
        current_char = '\0'; // EOF
    }
}

/**
 * @brief Skips over any whitespace characters in the input string.
 *        Advances the position until a non-whitespace character is encountered.
 */
void Lexer::skip_whitespace() {
    while (current_char != '\0' && std::isspace(current_char)) {
        advance();
    }
}

/**
 * @brief Extracts a numeric token from the input string.
 *        Handles both integer and floating-point numbers.
 * 
 * @return Token A token representing a number.
 */
Token Lexer::get_number() {
    std::string result;
    while (current_char != '\0' && std::isdigit(current_char)) {
        result += current_char;
        advance();
    }
    
    // Handle decimal point
    if (current_char == '.') {
        result += current_char;
        advance();
        
        while (current_char != '\0' && std::isdigit(current_char)) {
            result += current_char;
            advance();
        }
    }
    
    return Token(NUMBER, result);
}

/**
 * @brief Extracts an identifier token from the input string.
 *        Identifiers consist of alphanumeric characters and underscores.
 * 
 * @return Token A token representing an identifier.
 */
Token Lexer::get_identifier() {
    std::string result;
    while (current_char != '\0' && (std::isalnum(current_char) || current_char == '_')) {
        result += current_char;
        advance();
    }
    return Token(IDENTIFIER, result);
}

/**
 * @brief Retrieves the next token from the input string.
 *        Skips whitespace, identifies numbers, identifiers, and operators.
 *        Handles unknown characters by printing an error message.
 * 
 * @return Token The next token in the input string.
 */
Token Lexer::get_next_token() {
    while (current_char != '\0') {
        if (std::isspace(current_char)) {
            skip_whitespace();
            continue;
        }

        if (std::isdigit(current_char)) {
            return get_number();
        }
        
        if (std::isalpha(current_char) || current_char == '_') {
            return get_identifier();
        }

        switch (current_char) {
            case '+':
                advance();
                return Token(PLUS, "+");
            case '-':
                advance();
                return Token(MINUS, "-");
            case '*':
                advance();
                return Token(MULTIPLY, "*");
            case '/':
                advance();
                return Token(DIVIDE, "/");
            case '(':
                advance();
                return Token(LPAREN, "(");
            case ')':
                advance();
                return Token(RPAREN, ")");
            case '=':
                advance();
                return Token(EQUALS, "=");
            default:
                std::cerr << "Unknown character: " << current_char << std::endl;
                advance();
                break;
        }
    }

    return Token(EOF_TOKEN, "");
}

/**
 * @brief Tokenizes the entire input string into a sequence of tokens.
 *        Continues retrieving tokens until the end of input is reached.
 * 
 * @return std::vector<Token> A vector containing all tokens from the input string.
 */
std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;
    Token token = get_next_token();
    
    while (token.type != EOF_TOKEN) {
        tokens.push_back(token);
        token = get_next_token();
    }
    
    tokens.push_back(Token(EOF_TOKEN, ""));
    return tokens;
}