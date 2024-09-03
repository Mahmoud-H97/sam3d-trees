#include <cstdio>
#include <iostream>
#include <vector>
#include "rot_mat.hpp"
#include "apply_rot.hpp"



int main() {

	double resolution = 0.05;

	Point3D camera_pos = {0, 0, 80};




	double theta = M_PI / 4; //example angle 45 degrees
	
	std:: cout << "Rx(theta):" << std::endl;
	printMatrix(Rmx(theta));

	std:: cout << "Ry(theta):" << std::endl;
	printMatrix(Rmy(theta));

	std:: cout << "Rz(theta):" << std::endl;
	printMatrix(Rmz(theta));

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


