cmake_minimum_required(VERSION 3.8)
project(dynamic_systems_dsl_translator)

set(CMAKE_CXX_STANDARD 17)

FILE(COPY resources DESTINATION "${CMAKE_BINARY_DIR}")

set(SOURCE_FILES main.cpp SyntaxAnalyzer.cpp SyntaxAnalyzer.h CheckingResult.cpp CheckingResult.h StringUtils.cpp StringUtils.h Translator.cpp Translator.h)
add_executable(dynamic_systems_dsl_translator ${SOURCE_FILES})