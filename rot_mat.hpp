#ifndef ROT_MAT_HPP
#define ROT_MAT_HPP

#include <array>
#include <cmath>

//Define a 3x3 matrix type
using Matrix3x3 = std::array<std::array<double, 3>, 3>;

//declarations
Matrix3x3 Rx(double theta);
Matrix3x3 Ry(double theta);
Matrix3x3 Rz(double theta);

#endif //ROT_MAT_HPP
