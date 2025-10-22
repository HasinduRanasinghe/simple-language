#pragma once
#include <string>
#include <map>
#include "lexer.h"
#include "parser.h"

class Interpreter {
private:
    std::map<std::string, double> variables;

public:
    Interpreter();
    double evaluate(const std::string& text);
    void run();
    void run_file(const std::string& filename);
};