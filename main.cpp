#include <cstdio>
#include <iostream>
#include <vector>
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
        
	//Create another file for reading the files (load the files 
	//Add the las2txt command here to automatically witch .las/.laz files to .xyz
	//
	

        std::vector<Point3D> points;
	Point3D tempPt;

	//Reading points from ASCII formated file
	FILE* inFile = fopen("filename.xyz", "r");
	if (inFile) {
		while (fscanf(inFile, "%lf %lf %lf\n", &tempPt.x, &tempPt.y, &tempPt.z)=3)
		{
			points.push_back(tempPt);
		}
		fclose(inFile);
	}
	else {
		std::cout << "Error in loading the .xyz file" << std::endl;
		return 1;
	}

	//Parameters!
	//maybe for the angles and projections here
	
	}


