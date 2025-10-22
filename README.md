# Simple Programming Language Interpreter

A minimal programming language interpreter implemented in C++.

## Features

- Arithmetic expressions: +, -, *, /
- Variables and assignment
- Parenthesized expressions
- Interactive REPL (Read-Eval-Print Loop)
- File execution

## Project Structure

```
simple_language/
├── src/
│   ├── main.cpp              # Program entry point and CLI handler
│   ├── token.h               # Token type definitions and structure
│   ├── lexer.h               # Lexer class declaration
│   ├── lexer.cpp             # Lexical analyzer implementation
│   ├── parser.h              # Parser class declaration
│   ├── parser.cpp            # Syntax analyzer and AST builder
│   ├── ast.h                 # AST node class declarations
│   ├── ast.cpp               # AST node implementations and evaluation logic
│   ├── interpreter.h         # Interpreter class declaration
│   └── interpreter.cpp       # Main interpreter and REPL implementation
├── examples/
│   ├── arithmetic.txt        # Arithmetic operations examples
│   └── variables.txt         # Variable usage examples
├── CMakeLists.txt            # CMake build configuration
└── README.md                 # Project documentation
```

## File Descriptions

### Core Components

- **`token.h`** - Defines token types (NUMBER, PLUS, MINUS, etc.) and the Token structure used throughout the lexing and parsing stages.

- **`lexer.h` / `lexer.cpp`** - Implements the lexical analyzer that converts source code text into a stream of tokens. Handles number parsing, identifier recognition, and operator detection.

- **`parser.h` / `parser.cpp`** - Implements a recursive descent parser that transforms tokens into an Abstract Syntax Tree (AST). Handles operator precedence and syntax validation.

- **`ast.h` / `ast.cpp`** - Defines AST node classes (NumberNode, BinaryOpNode, VariableNode, AssignmentNode) and implements the evaluation logic for each node type.

- **`interpreter.h` / `interpreter.cpp`** - Coordinates the lexer, parser, and evaluator. Manages variable storage and provides both REPL and file execution modes.

- **`main.cpp`** - Entry point that handles command-line arguments and launches the interpreter in interactive or file execution mode.

### Configuration & Examples

- **`CMakeLists.txt`** - CMake build configuration specifying compiler settings, source files, and build targets.

- **`examples/arithmetic.txt`** - Sample programs demonstrating arithmetic operations and operator precedence.

- **`examples/variables.txt`** - Sample programs showing variable declaration, assignment, and usage.

## Building

Use a CMake file to build the program.

```
mkdir build
cd build
cmake ..
make
```

## Usage

### Interactive Mode

```
./simple_lang
```

### Run a Program File

```
./simple_lang examples/arithmetic.txt
```

### Interactive Mode After Running a File

```
./simple_lang -i examples/variables.txt
```

## Language Syntax

### Arithmetic

```
2 + 3
10 - 2 * 3
(5 + 3) * 2
```

### Variables

```
x = 10
y = 5
x + y
```

## Future Improvements

- Control structures (if/else, loops)
- Functions
- More data types (strings, arrays)
- Improved error handling
