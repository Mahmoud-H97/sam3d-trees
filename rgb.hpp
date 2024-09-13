#ifndef RGB_HPP
#define RGB_HPP
#include <cstdlib>
#include <stdexcept>

struct rgb {
    int r;
    int g;
    int b;

    // Overload the subscript operator for indexing if needed.
    int& operator[](int index) {
        if (index == 0) return r;
        if (index == 1) return g;
        if (index == 2) return b;
        throw std::out_of_range("Index out of range");
    }

    const int& operator[](int index) const {
        if (index == 0) return r;
        if (index == 1) return g;
        if (index == 2) return b;
        throw std::out_of_range("Index out of range");
    }
};

#endif 

