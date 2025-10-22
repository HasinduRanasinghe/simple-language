#include "interpreter.h"
#include <iostream>
#include <fstream>
#include <sstream>

/**
 * @brief Constructs an Interpreter object.
 *        Initializes the interpreter with an empty variable map.
 */
Interpreter::Interpreter() {}

/**
 * @brief Evaluates a line of input text as an expression.
 *        Tokenizes the input, parses it into an AST, and evaluates the AST.
 *        Handles exceptions and prints errors to standard error.
 * 
 * @param text The input string to be evaluated.
 * @return double The result of the evaluated expression, or 0 if an error occurs.
 */
double Interpreter::evaluate(const std::string& text) {
    Lexer lexer(text);
    std::vector<Token> tokens = lexer.tokenize();
    Parser parser(tokens);
    
    try {
        auto ast = parser.parse();
        return ast->evaluate(variables);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 0;
    }
}

/**
 * @brief Runs the interpreter in interactive mode.
 *        Reads input from the user, evaluates each line, and prints the result.
 *        Continues until the user types 'exit'.
 */
void Interpreter::run() {
    std::string input;
    
    std::cout << "Simple Language Interpreter (type 'exit' to quit)\n";
    
    while (true) {
        std::cout << ">> ";
        std::getline(std::cin, input);
        
        if (input == "exit") {
            break;
        }
        
        try {
            double result = evaluate(input);
            std::cout << result << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
}

/**
 * @brief Runs the interpreter on a file.
 *        Reads each line from the file, evaluates it, and prints the result with line numbers.
 *        Skips empty lines and lines starting with '#' (comments).
 *        Handles file opening errors and evaluation exceptions.
 * 
 * @param filename The name of the file to interpret.
 */
void Interpreter::run_file(const std::string& filename) {
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        std::cerr << "Could not open file: " << filename << std::endl;
        return;
    }
    
    std::string line;
    int line_number = 1;
    
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') {
            // Skip empty lines and comments
            line_number++;
            continue;
        }
        
        try {
            double result = evaluate(line);
            std::cout << "Line " << line_number << ": " << result << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Error at line " << line_number << ": " << e.what() << std::endl;
        }
        
        line_number++;
    }
}