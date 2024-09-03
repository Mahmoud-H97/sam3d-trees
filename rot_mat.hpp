#ifndef ROT_MAT_HPP
#define ROT_MAT_HPP

#include <array>
#include <cmath>

//Define a 3x3 matrix type
using Matrix3x3 = std::array<std::array<double, 3>, 3>;

//declarations
Matrix3x3 Rmx(double theta);
Matrix3x3 Rmy(double theta);
Matrix3x3 Rmz(double theta);
void printMatrix (const Matrix3x3& matrix);

#endif //ROT_MAT_HPP
