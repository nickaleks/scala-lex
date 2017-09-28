cmake_minimum_required(VERSION 3.6 FATAL_ERROR)
project(myproject VERSION 0.1 LANGUAGES CXX)

add_executable(scala-lex
    lexer.cpp
    main.cpp
        token.cpp)
set(CMAKE_CXX_FLAGS "-std=c++1z  -Wextra -Wall -Wundef -Wpointer-arith -Wno-sign-compare")