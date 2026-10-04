#pragma once

#include <cstddef>
#include <string>
#include <vector>

class Matrix {
public:
    Matrix() = default;
    explicit Matrix(std::size_t size);

    std::size_t size() const noexcept;

    double& operator()(std::size_t row, std::size_t col);
    double operator()(std::size_t row, std::size_t col) const;

    static Matrix readFromFile(const std::string& filename);
    void writeToFile(const std::string& filename) const;

private:
    std::size_t n_ = 0;
    std::vector<double> data_;
};

Matrix multiply(const Matrix& a, const Matrix& b);
