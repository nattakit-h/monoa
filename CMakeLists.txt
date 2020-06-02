cmake_minimum_required(VERSION 3.14)
project(monoa LANGUAGES CXX)

# set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Excecutable

add_executable(monoa)

target_sources(monoa PRIVATE
  src/command.cpp
  src/token.cpp
  src/lexer.cpp)

set_property(TARGET monoa PROPERTY CXX_STANDARD 17)

target_include_directories(monoa PRIVATE ${CMAKE_SOURCE_DIR}/src)
