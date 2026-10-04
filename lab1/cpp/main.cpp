#include "matrix.h"

#include <chrono>
#include <cstddef>
#include <exception>
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr
            << "Usage: matrix_multiplication <matrix_a> <matrix_b> <result>\n";
        return 1;
    }

    try {
        const std::string matrixAFile = argv[1];
        const std::string matrixBFile = argv[2];
        const std::string resultFile = argv[3];

        const Matrix a = Matrix::readFromFile(matrixAFile);
        const Matrix b = Matrix::readFromFile(matrixBFile);

        if (a.size() != b.size()) {
            throw std::runtime_error("Matrices must have the same dimensions");
        }

        const std::size_t n = a.size();

        const auto start = std::chrono::high_resolution_clock::now();
        const Matrix result = multiply(a, b);
        const auto finish = std::chrono::high_resolution_clock::now();

        const std::chrono::duration<double> elapsed = finish - start;

        result.writeToFile(resultFile);

        const unsigned long long operations =
            static_cast<unsigned long long>(n) *
            static_cast<unsigned long long>(n) *
            static_cast<unsigned long long>(n);

        std::cout << "Matrix multiplication completed.\n";
        std::cout << "Matrix size: " << n << " x " << n << '\n';
        std::cout << "Elements in one matrix: " << n * n << '\n';
        std::cout << "Multiplications: " << operations << '\n';
        std::cout << "Approximate additions: "
                  << operations - n * n << '\n';
        std::cout << "Execution time: " << elapsed.count() << " sec\n";
        std::cout << "Result: " << resultFile << '\n';

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }

    return 0;
}
