#include "matrix.h"

#include <fstream>
#include <iomanip>
#include <stdexcept>

Matrix::Matrix(std::size_t size)
    : size_(size), data_(size * size, 0.0) {}

std::size_t Matrix::size() const noexcept {
    return size_;
}

double& Matrix::operator()(
    std::size_t row,
    std::size_t column
) {
    return data_[row * size_ + column];
}

double Matrix::operator()(
    std::size_t row,
    std::size_t column
) const {
    return data_[row * size_ + column];
}

Matrix Matrix::readFromFile(const std::string& filename) {
    std::ifstream input(filename);

    if (!input) {
        throw std::runtime_error(
            "Cannot open input file: " + filename
        );
    }

    std::size_t n{};

    if (!(input >> n) || n == 0) {
        throw std::runtime_error(
            "Invalid matrix size in: " + filename
        );
    }

    Matrix matrix(n);

    for (std::size_t i = 0; i < n; ++i) {
        for (std::size_t j = 0; j < n; ++j) {
            if (!(input >> matrix(i, j))) {
                throw std::runtime_error(
                    "Invalid matrix data in: " + filename
                );
            }
        }
    }

    return matrix;
}

void Matrix::writeToFile(
    const std::string& filename
) const {
    std::ofstream output(filename);

    if (!output) {
        throw std::runtime_error(
            "Cannot create output file: " + filename
        );
    }

    output << size_ << '\n';
    output << std::setprecision(15);

    for (std::size_t i = 0; i < size_; ++i) {
        for (std::size_t j = 0; j < size_; ++j) {
            if (j != 0) {
                output << ' ';
            }

            output << (*this)(i, j);
        }

        output << '\n';
    }
}

Matrix multiply(
    const Matrix& a,
    const Matrix& b
) {
    if (a.size() != b.size()) {
        throw std::invalid_argument(
            "Matrices must have the same dimensions"
        );
    }

    const std::size_t n = a.size();
    Matrix result(n);

    // Classical sequential O(N^3) multiplication.
    for (std::size_t i = 0; i < n; ++i) {
        for (std::size_t k = 0; k < n; ++k) {
            const double a_ik = a(i, k);

            for (std::size_t j = 0; j < n; ++j) {
                result(i, j) += a_ik * b(k, j);
            }
        }
    }

    return result;
}
