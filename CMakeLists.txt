cmake_minimum_required(VERSION 3.10)
project(SimpleLang)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(simple_lang
    src/main.cpp
    src/lexer.cpp
    src/parser.cpp
    src/ast.cpp
    src/interpreter.cpp
)

target_include_directories(simple_lang PRIVATE src)