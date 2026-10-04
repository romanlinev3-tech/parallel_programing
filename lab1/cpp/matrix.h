#pragma once

#include <cstddef>
#include <string>
#include <vector>

class Matrix {
public:
    explicit Matrix(std::size_t size);

    [[nodiscard]] std::size_t size() const noexcept;

    double& operator()(std::size_t row, std::size_t column);
    [[nodiscard]] double operator()(
        std::size_t row,
        std::size_t column
    ) const;

    [[nodiscard]] static Matrix readFromFile(
        const std::string& filename
    );

    void writeToFile(const std::string& filename) const;

private:
    std::size_t size_{};
    std::vector<double> data_;
};

[[nodiscard]] Matrix multiply(
    const Matrix& a,
    const Matrix& b
);
