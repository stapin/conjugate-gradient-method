#include "Vector.hpp"

VectorDouble& VectorDouble::operator+=(VectorDouble other) {
    if (this->size() != other.size()) {
        throw std::invalid_argument("vectors have different sizes while operator");
    }
    for (size_t i = 0; i < other.size(); ++i) {
        this->operator[](i) += other[i];
    }
    return *this;
}

VectorDouble& VectorDouble::operator-=(VectorDouble other) {
    if (this->size() != other.size()) {
        throw std::invalid_argument("vectors have different sizes while operator");
    }
    for (size_t i = 0; i < other.size(); ++i) {
        this->operator[](i) -= other[i];
    }
    return *this;
}

VectorDouble operator+(VectorDouble v1, VectorDouble v2) {
    return v1 += v2;
}

VectorDouble operator-(VectorDouble v) {
    for (size_t i = 0; i < v.size(); ++i) {
        v[i] = -v[i];
    }
    return v; // rvo or move
}

VectorDouble operator-(VectorDouble v1, VectorDouble v2) {
    return v1 -= v2;
}

VectorDouble operator*(double a, VectorDouble other) {
    for (size_t i = 0; i < other.size(); ++i) {
        other[i] *= a;
    }
    return other;
}

void print_vec(const VectorDouble& vec) {
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << " ";
    }
    std::cout << "\n";
}