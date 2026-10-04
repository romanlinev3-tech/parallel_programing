#include "matrix.h"

#include <fstream>
#include <iomanip>
#include <stdexcept>

Matrix::Matrix(std::size_t size)
    : n_(size), data_(size * size, 0.0) {}

std::size_t Matrix::size() const noexcept {
    return n_;
}

double& Matrix::operator()(std::size_t row, std::size_t col) {
    return data_[row * n_ + col];
}

double Matrix::operator()(std::size_t row, std::size_t col) const {
    return data_[row * n_ + col];
}

Matrix Matrix::readFromFile(const std::string& filename) {
    std::ifstream input(filename);

    if (!input) {
        throw std::runtime_error("Cannot open file: " + filename);
    }

    std::size_t n;
    input >> n;

    if (!input || n == 0) {
        throw std::runtime_error("Invalid matrix size in: " + filename);
    }

    Matrix matrix(n);

    for (std::size_t i = 0; i < n; ++i) {
        for (std::size_t j = 0; j < n; ++j) {
            if (!(input >> matrix(i, j))) {
                throw std::runtime_error("Invalid matrix data in: " + filename);
            }
        }
    }

    return matrix;
}

void Matrix::writeToFile(const std::string& filename) const {
    std::ofstream output(filename);

    if (!output) {
        throw std::runtime_error("Cannot open output file: " + filename);
    }

    output << n_ << '\n';
    output << std::setprecision(15);

    for (std::size_t i = 0; i < n_; ++i) {
        for (std::size_t j = 0; j < n_; ++j) {
            if (j != 0) {
                output << ' ';
            }
            output << (*this)(i, j);
        }
        output << '\n';
    }
}

Matrix multiply(const Matrix& a, const Matrix& b) {
    if (a.size() != b.size()) {
        throw std::invalid_argument("Matrices must have the same size");
    }

    const std::size_t n = a.size();
    Matrix result(n);

    // Classical O(N^3) matrix multiplication.
    for (std::size_t i = 0; i < n; ++i) {
        for (std::size_t k = 0; k < n; ++k) {
            const double aik = a(i, k);

            for (std::size_t j = 0; j < n; ++j) {
                result(i, j) += aik * b(k, j);
            }
        }
    }

    return result;
}
