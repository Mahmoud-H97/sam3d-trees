#include "rot_mat.hpp"

//Define a 3x3 matrix 
using Matrix3x3 = std::array<std::array<double, 3>, 3> ;

//Rotation matrix around the x-axis
Matrix3x3 Rx(double theta) {
	Matrix3x3 rx = {{
		{1, 0, 0},
		{0, std::cos(theta), -std::sin(theta)},
		{0, std::sin(theta), std::cos(theta)}
	}};
	return rx;
}

//Rotation matrix around the y-axis
Matrix3x3 Ry(double theta) {
	Matrix3x3 ry = {{
		{std::cos(theta), 0, std::sin(theta)},
		{0, 1, 0},
		{-std::sin(theta), 0, std::cos(theta)}
	}};
	return ry;
}

//Rotation matrix around the z-axis
Matrix3x3 Rz(double theta) {
	Matrix3x3 rz = {{
		{std::cos(theta), -std::sin(theta), 0},
		{std::sin(theta), std::cos(theta), 0},
		{0,0, 1}
	}};
	return rz;
}

