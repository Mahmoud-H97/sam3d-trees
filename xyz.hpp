#ifndef XYZ_HPP
#define XYZ_HPP
#include <stdexcept>

struct xyz {
    double x;
    double y;
    double z;

    // Overload the subscript operator for indexing if needed.
    double& operator[](int index) {
        if (index == 0) return x;
        if (index == 1) return y;
        if (index == 2) return z;
        throw std::out_of_range("Index out of range");
    }

    const double& operator[](int index) const {
        if (index == 0) return x;
        if (index == 1) return y;
        if (index == 2) return z;
        throw std::out_of_range("Index out of range");
    }
};

#endif // XYZ_HPP

