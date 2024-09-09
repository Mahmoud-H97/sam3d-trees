#include <complex>
#include <cstdio>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
#include "rot_mat.hpp"
#include "apply_rot.hpp"
#include "las2xyz.hpp"
#include "las2rgb.hpp"

// to be runned as ./main inputfilename.las res cam_pos angles coloring
// for the coloring maybe start with focusing in Z, intensity and numberofreturns (in future think about Amp and infrared) 

//Functiion to parse a string like "{(60, 0), (-60,0), (0, 60), ...}" input from the argv[] into a vector of angle pairs 
std::vector<std::pair<double, double>> parse_angels(const std::string& angle_input){
	std::vector<std::pair<double, double>> angles;
	std::stringstream ss(angle_input);
	char discard; //to discard unnecessary characters
	double angle1, angle2;

	while (ss >> discard >> angle1 >> discard >> angle2 >> discard) {
		angles.emplace_back(angle1, angle2);
	}
	return angles;
}

//Function to parse camera positions input like "(x,y,z)" into a vector  
std::vector<double> parse_cam_pos (const std::string& cam_pos_input){
	std::vector<double> cam_pos(3);
	sscanf(cam_pos_input.c_str(), "(%lf, %lf, %lf)" , &cam_pos[0], &cam_pos[1], &cam_pos[2]);
	return cam_pos;
}

int main(int argc, char* argv[]) {

	if (argc != 6) {
		std::cerr << "Usage: " << argv[0] << " input_filename.las/laz  Resolution  Camera Position  Viewing Angles  Coloring Dimension (Currently rgb only) " << std::endl;
		return 1;
	}

	std::string input_filename = argv[1];
	//std::double resolution = argv[2];
	std::vector<double> cam_pos = parse_cam_pos(argv[3]);
	std::vector<std::pair<double, double>> angles = parse_angels(argv[4]);
	std::string coloring = argv[5];

	//create the xyz and coloring ASCII formated files

	las2xyz(input_filename);

	std::cout << "las2xyz completed" << std::endl;

	las2rgb(input_filename);

	std::cout << "las2rgb completed" << std::endl;

	std::vector<xyz> points;  //used a different points structure here to not mess the old one's logic (Point3D)...
	xyz tempPt;
	//Reading points from ASCII formated file
	FILE* inFile = fopen("tmp.xyz", "r");
	if (inFile) {
		while (fscanf(inFile, "%lf %lf %lf\n", &tempPt.x, &tempPt.y, &tempPt.z) == 3)
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
		
		double theta_x = angle.first * pi / 180;
		double theta_y = angle.second * pi / 180;
		
		Matrix3x3 Rm_x = Rmx(theta_x);
		Matrix3x3 Rm_y = Rmy(theta_y);

		std::vector<xyz> rot_points = ApplyRotation(points, Rm_x, Rm_y, cam_pos);
		//std::vector<xyz> rot_points = ApplyRotation(points, Rmx(theta_x), Rmy(theta_y), cam_pos);
		std::cout << "completed rotation with angle: (" << angle.first << ", " << angle.second << ")" <<  std::endl;
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


