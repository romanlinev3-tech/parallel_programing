#include "matrix.h"

#include <chrono>
#include <cstdint>
#include <iostream>
#include <stdexcept>
#include <string>

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr
            << "Usage: matrix_multiplication "
            << "<matrix_a> <matrix_b> <result>\n";
        return 1;
    }

    try {
        const std::string matrix_a_file = argv[1];
        const std::string matrix_b_file = argv[2];
        const std::string result_file = argv[3];

        const Matrix a = Matrix::readFromFile(matrix_a_file);
        const Matrix b = Matrix::readFromFile(matrix_b_file);

        if (a.size() != b.size()) {
            throw std::invalid_argument(
                "Matrices must have the same dimensions"
            );
        }

        const std::size_t n = a.size();

        const auto start = std::chrono::steady_clock::now();

        const Matrix result = multiply(a, b);

        const auto finish = std::chrono::steady_clock::now();

        const std::chrono::duration<double> elapsed =
            finish - start;

        result.writeToFile(result_file);

        const std::uint64_t nn =
            static_cast<std::uint64_t>(n) *
            static_cast<std::uint64_t>(n);

        const std::uint64_t multiplications = nn * n;
        const std::uint64_t additions =
            nn * (n - 1);

        const std::uint64_t total_operations =
            multiplications + additions;

        const double gflops =
            static_cast<double>(total_operations) /
            elapsed.count() /
            1'000'000'000.0;

        const double memory_mb =
            static_cast<double>(3 * nn * sizeof(double)) /
            (1024.0 * 1024.0);

        std::cout << "Matrix multiplication completed.\n";
        std::cout << "Matrix size: "
                  << n << " x " << n << '\n';
        std::cout << "Elements in one matrix: "
                  << nn << '\n';
        std::cout << "Multiplications: "
                  << multiplications << '\n';
        std::cout << "Additions: "
                  << additions << '\n';
        std::cout << "Total arithmetic operations: "
                  << total_operations << '\n';
        std::cout << "Approximate memory for A, B and C: "
                  << memory_mb << " MB\n";
        std::cout << "Execution time: "
                  << elapsed.count() << " sec\n";
        std::cout << "Performance: "
                  << gflops << " GFLOPS\n";
        std::cout << "Result file: "
                  << result_file << '\n';

    } catch (const std::exception& error) {
        std::cerr << "Error: "
                  << error.what() << '\n';
        return 1;
    }

    return 0;
}
