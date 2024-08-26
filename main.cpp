#include <iostream>
#include "rot_mat.hpp"

//print the matrix (for testing)
void printMatrix(const Matrix3x3& matrix){
	for (const auto& row : matrix) {
		for (const auto& elem : row) {
			std::cout << elem << " ";
		}
		std::cout << std::endl;
	}
}

int main() {
	double theta = M_PI / 4; //example angle 45 degrees
	
	std:: cout << "Rx(theta):" << std::endl;
	printMatrix(Rx(theta));

	std:: cout << "Ry(theta):" << std::endl;
	printMatrix(Ry(theta));

	std:: cout << "Rz(theta):" << std::endl;
	printMatrix(Rz(theta));

	return 0;

}


