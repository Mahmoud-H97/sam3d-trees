#include <complex>
#include <cstdio>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
//#include <strstream>
#include <utility>
#include <vector>
#include "create_image.hpp"
#include "rot_mat.hpp"
#include "apply_rot.hpp"
#include "las2xyz.hpp"
#include "las2rgb.hpp"
#include "rgb.hpp"

// to be runned as ./main inputfilename.las res cam_pos angles coloring
// for the coloring maybe start with focusing in Z, intensity and numberofreturns (in future think about Amp and infrared) 

//Functiion to parse a string like "{(60, 0), (-60,0), (0, 60), ...}" input from the argv[] into a vector of angle pairs 

std::vector<std::pair<double, double>> parse_angles(const std::string& angle_input) {
    std::vector<std::pair<double, double>> angles;
    std::stringstream ss(angle_input);
    char discard; // To discard unnecessary characters
    double angle1, angle2;

    // Ignore the opening brace '{'
    ss >> discard;

    while (ss >> discard >> angle1 >> discard >> angle2 >> discard) {
        // Push the parsed angles into the vector
        angles.emplace_back(angle1, angle2);

        // Check if there's a comma and discard it
        ss >> discard;
        if (discard == '}') {
            break; // End of input
        }
    }

    return angles;
}

//Function to parse camera positions input like "(x,y,z)" into a vector  
std::vector<double> parse_cam_pos (const std::string& cam_pos_input){
	std::vector<double> cam_pos(3);
	sscanf(cam_pos_input.c_str(), "(%lf, %lf, %lf)" , &cam_pos[0], &cam_pos[1], &cam_pos[2]);
	return cam_pos;
}
//Function to parse resolution input into a float  
double parse_res (const std::string& res_input){
	double res;
	std::stringstream s;
	s << res_input;
	s >> res;
	return res;
}


int main(int argc, char* argv[]) {

	if (argc != 6) {
		std::cerr << "Usage: " << argv[0] << " input_filename.las/laz  Resolution  Camera Position  Viewing Angles  Coloring Dimension (Currently rgb only) " << std::endl;
		return 1;
	}

	std::string input_filename = argv[1];
	double resolution = parse_res(argv[2]);
	std::vector<double> cam_pos = parse_cam_pos(argv[3]);
	std::vector<std::pair<double, double>> angles = parse_angles(argv[4]);
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


	std::vector<rgb> colors;  //used a different points structure here to not mess the old one's logic (Point3D)...
	rgb tempCol;
	//Reading points from ASCII formated file
	FILE* ColInFile = fopen("tmp.rgb", "r");
	if (ColInFile) {
		while (fscanf(inFile, "%d %d %d\n", &tempCol.r, &tempCol.g, &tempCol.b) == 3)
		{
			colors.push_back(tempCol);
		}
		fclose(ColInFile);

	}
	else {
		std::cout << "Error in loading the .rgb file" << std::endl;
		return 1;
	}

	//create the rotation matrices based on the input angles and apply rotation
	double pi = 3.14159265359 ;

	std::cout << "Number of angles: " << angles.size() << std::endl;
	
	std::cout << "Resolution will be: " << resolution << std::endl;

//	std::cout << "1st angle's X:  " << std::to_string(angles[0].first) << "Y:  " << std::to_string(angles[0].second)  << std::endl; //TODO::segmentation fault in here!! 

	for (const auto& angle : angles) {

		double theta_x = angle.first * pi / 180;
		double theta_y = angle.second * pi / 180;

		Matrix3x3 Rm_x = Rmx(theta_x);
		Matrix3x3 Rm_y = Rmy(theta_y);

		//Just for tracking, remove later...
		printMatrix(Rm_x);
		printMatrix(Rm_y);



		std::vector<xyz> rot_points = ApplyRotation(points, Rm_x, Rm_y, cam_pos);
		//std::vector<xyz> rot_points = ApplyRotation(points, Rmx(theta_x), Rmy(theta_y), cam_pos);

		std::string output_filename = "output_" + std::to_string(angle.first) + "_" + std::to_string(angle.second) + ".jpeg";

		std::cout << "For angle: " << std::to_string(angle.first) << ", " << std::to_string(angle.second)  << " the generated filename will be: " << output_filename << std::endl;


		//create image
		IFPC(rot_points, colors, resolution , output_filename);
	}

	std::cout << "completed rotation with all angle" <<  std::endl;
	//
	
	





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


