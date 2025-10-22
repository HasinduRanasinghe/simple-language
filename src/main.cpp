#include <iostream>
#include <string>
#include "interpreter.h"

void print_help() {
    std::cout << "Usage: simple_lang [options] [file]\n";
    std::cout << "Options:\n";
    std::cout << "  -h, --help    Display this help message\n";
    std::cout << "  -i, --interactive  Run in interactive mode after executing file\n";
    std::cout << "If no file is specified, the interpreter runs in interactive mode.\n";
}

int main(int argc, char* argv[]) {
    Interpreter interpreter;
    
    if (argc == 1) {
        // No arguments, run in interactive mode
        interpreter.run();
        return 0;
    }
    
    std::string arg1 = argv[1];
    
    if (arg1 == "-h" || arg1 == "--help") {
        print_help();
        return 0;
    }
    
    if (arg1 == "-i" || arg1 == "--interactive") {
        if (argc > 2) {
            // Run file first, then interactive mode
            interpreter.run_file(argv[2]);
        }
        interpreter.run();
    } else {
        // Run file only
        interpreter.run_file(arg1);
    }
    
    return 0;
}