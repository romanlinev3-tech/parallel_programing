cmake_minimum_required(VERSION 3.20)

project(MatrixMultiplication LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(matrix_multiplication
    lab1/cpp/main.cpp
    lab1/cpp/matrix.cpp
    lab1/cpp/matrix.h
)

if (MSVC)
    target_compile_options(matrix_multiplication PRIVATE /W4)
else()
    target_compile_options(matrix_multiplication PRIVATE -Wall -Wextra -Wpedantic)
endif()
