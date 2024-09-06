#include <complex>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include "rot_mat.hpp"
#include "apply_rot.hpp"
#include "las2xyz.hpp"
#include "las2rgb.hpp"

// to be runned as ./main inputfilename.las res cam_pos angles coloring
// for the coloring maybe start with focusing in Z, intensity and numberofreturns (in future think about Amp and infrared) 

struct xyz { 
	double x, y, z;
};


int main(int argc, char* argv[]) {

	if (argc != 6) {
		std::cerr << "Usage: " << argv[0] << " input_filename.las/laz  Resolution  Camera Position  Viewing Angles  Coloring Dimension (Currently rgb only) " << std::endl;
		return 1;
	}

	std::string input_filename = argv[1];
	//std::double resolution = argv[2];
	std::vector<double> cam_pos = argv[3];
	std::vector<double> angles = argv[4];
	std::string coloring = argv[5];

	//create the xyz and coloring ASCII formated files

	las2xyz(input_filename);

	std::cout << "las2xyz completed" << std::endl;

	las2rgb(input_filename);

	std::cout << "las2rgb completed" << std::endl;
	//

	std::vector<Point3D> points;
	Point3D tempPt;
	//Reading points from ASCII formated file
	FILE* inFile = fopen("tmp.xyz", "r");
	if (inFile) {
		while (fscanf(inFile, "%lf %lf %lf\n", &tempPt[0], &tempPt[1], &tempPt[2]) == 3)
		{
			points.push_back(tempPt);
		}
		fclose(inFile);

	}
	else {
		std::cout << "Error in loading the .xyz file" << std::endl;
		return 1;
	}

	//create the rotation matrices based on the input angles
	double pi = 3.14159265359 ;

	for (const auto& angle : angles) {

		double theta_x = angle[0] * pi / 180;
		double theta_y = angle[1] * pi / 180;
		
		Rmx(theta_x);
		Rmy(theta_y);

		ApplyRotation(points, Rmx(theta_x), Rmy(theta_y), cam_pos);

		}

	//apply rotation to the points 
	//
	//create image 





	//Point3D camera_pos = {0, 0, 80};
	//angles here (argument from the main compiled program)
	//then a for loop 

	//double theta_x = 
	//double theta_y = 
	//double theta_z = 

	//




	//	double theta = M_PI / 4; //example angle 45 degrees

	//	std:: cout << "Rmx(theta):" << std::endl;
	//	printMatrix(Rmx(theta_x));

	//	std:: cout << "Rmy(theta):" << std::endl;
	//	printMatrix(Rmy(theta_y));

	//	std:: cout << "Rmz(theta):" << std::endl;
	//	printMatrix(Rmz(theta_z));


	//Create another file for reading the files (load the files 
	//Add the las2txt command here to automatically witch .las/.laz files to .xyz






	//Parameters!
	//maybe for the angles and projections here

	return 0;

}


