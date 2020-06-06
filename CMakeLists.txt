cmake_minimum_required(VERSION 3.14)
project(monoa LANGUAGES CXX)

# set(CMAKE_CXX_STANDARD 17)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Excecutable

add_executable(monoa)

target_sources(monoa PRIVATE
  src/ast/ast.cpp
  src/ast/printer.cpp
  src/parser/parser.cpp
  src/parser/token.cpp
  src/parser/lexer.cpp
  src/command.cpp)

set_property(TARGET monoa PROPERTY CXX_STANDARD 17)

target_include_directories(monoa PRIVATE ${CMAKE_SOURCE_DIR}/src)
