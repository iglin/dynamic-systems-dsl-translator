cmake_minimum_required(VERSION 3.8)
project(dynamic_systems_dsl_translator)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp SyntaxAnalyzer.cpp SyntaxAnalyzer.h CheckingResult.cpp CheckingResult.h)
add_executable(dynamic_systems_dsl_translator ${SOURCE_FILES})