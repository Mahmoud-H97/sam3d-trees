#include <pdal/PipelineManager.hpp>
#include <pdal/PointView.hpp>
#include <iostream>
#include <fstream>


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

//Function to parse resolution input into a float  
double parse_res (const std::string& res_input){
	double res;
	std::stringstream s;
	s << res_input;
	s >> res;
	return res;
}


// Define a 4x4 matrix
using Matrix4x4 = std::array<std::array<double, 4>, 4>;

// Rotation matrix around the x-axis (4x4 version)
Matrix4x4 Rmx_4x4(double theta) {
    Matrix4x4 rmx = {{
        {1, 0, 0, 0},
        {0, std::cos(theta), -std::sin(theta), 0},
        {0, std::sin(theta), std::cos(theta), 0},
        {0, 0, 0, 1}
    }};
    return rmx;
}

// Rotation matrix around the y-axis (4x4 version)
Matrix4x4 Rmy_4x4(double theta) {
    Matrix4x4 rmy = {{
        {std::cos(theta), 0, std::sin(theta), 0},
        {0, 1, 0, 0},
        {-std::sin(theta), 0, std::cos(theta), 0},
        {0, 0, 0, 1}
    }};
    return rmy;
}


void las2tif(int argc, char* argv[]) {
	if (argc != 5) {
		std::cerr << "Usage: " << argv[0] << "input filename.las/laz  Resolustion  Viewing Angles  Dimension to be rasterized" << std::endl;
		return ;
	}

	
	std::string input_filename = argv[1];
	double resolution = parse_res(argv[2]);
	std::vector<std::pair<double, double>> angles = parse_angles(argv[3]);
	std::string dim = argv[4];

    // Check if input_filename is empty
    if (input_filename.empty()) {
        std::cerr << "Error: input filename is empty!" << std::endl;
        return;
    }

    // Check if file exists
    std::ifstream file(input_filename);
    if (!file.good()) {
        std::cerr << "Error: input file does not exist: " << input_filename << std::endl;
        return;
    }
    file.close();

    pdal::PipelineManager pipelineManager;
    
    std::string pipeline = R"json(
    [
        {
            "type": "readers.las",
            "filename": ")json" + input_filename + R"json("
        },
        {
	    "type": "filters.transformation",
	    "matrix": ""
	},
	{
	    "type": "filters.hexbin",
	    "edge_length": 0.5
	},
        {
            "type": "writers.text",
            "filename": "outputfile.txt",
            "order": "X Y Z"
        }
    ]
    )json";

    // Validate and execute pipeline
    try {
        pipelineManager.readPipeline(pipeline);
        pipelineManager.execute();
    } catch (const pdal::pdal_error& e) {
        std::cerr << "PDAL Error: " << e.what() << std::endl;
    }
}

