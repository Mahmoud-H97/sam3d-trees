#include "rot_mat.hpp"
#include <iostream>

//Define a 3x3 matrix 
using Matrix3x3 = std::array<std::array<double, 3>, 3> ;

//Rotation matrix around the x-axis
Matrix3x3 Rx(double theta) {
	Matrix3x3 rmx = {{
		{1, 0, 0},
		{0, std::cos(theta), -std::sin(theta)},
		{0, std::sin(theta), std::cos(theta)}
	}};
	return rmx;
}

//Rotation matrix around the y-axis
Matrix3x3 Ry(double theta) {
	Matrix3x3 rmy = {{
		{std::cos(theta), 0, std::sin(theta)},
		{0, 1, 0},
		{-std::sin(theta), 0, std::cos(theta)}
	}};
	return rmy;
}

//Rotation matrix around the z-axis
Matrix3x3 Rz(double theta) {
	Matrix3x3 rmz = {{
		{std::cos(theta), -std::sin(theta), 0},
		{std::sin(theta), std::cos(theta), 0},
		{0,0, 1}
	}};
	return rmz;
}

//print the matrix (for testing)
void printMatrix(const Matrix3x3& matrix){
	for (const auto& row : matrix) {
		for (const auto& elem : row) {
			std::cout << elem << " ";
		}
		std::cout << std::endl;
	}
}

