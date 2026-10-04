cmake_minimum_required(VERSION 3.20)

project(ParallelProgramming
    VERSION 1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(matrix_multiplication
    lab1/cpp/main.cpp
    lab1/cpp/matrix.cpp
)

target_include_directories(matrix_multiplication
    PRIVATE
        lab1/cpp
)

if(MSVC)
    target_compile_options(matrix_multiplication PRIVATE
        /W4
        /permissive-
    )
else()
    target_compile_options(matrix_multiplication PRIVATE
        -Wall
        -Wextra
        -Wpedantic
    )
endif()
