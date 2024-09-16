#include <ctime>
#include <pdal/PipelineManager.hpp>
#include <pdal/PointView.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <array>
#include <utility>

// Function to parse a string like "{(60, 0), (-60,0), (0, 60), ...}" input from the argv[] into a vector of angle pairs 
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

        // Check if there's a closing brace '}'
        if (ss.peek() == '}') {
            break; // End of input
        }
    }

    return angles;
}

// Function to parse resolution input into a double  
double parse_res(const std::string& res_input) {
    double res;
    std::stringstream s(res_input);
    s >> res;
    return res;
}

// Define a 4x4 matrix
using Matrix4x4 = std::array<std::array<double, 4>, 4>;

// Rotation matrix around the x-axis (4x4 version)
Matrix4x4 Rmx_4x4(double theta) {
    return {{
        {1, 0, 0, 0},
        {0, std::cos(theta), -std::sin(theta), 0},
        {0, std::sin(theta), std::cos(theta), 0},
        {0, 0, 0, 1}
    }};
}

// Rotation matrix around the y-axis (4x4 version)
Matrix4x4 Rmy_4x4(double theta) {
    return {{
        {std::cos(theta), 0, std::sin(theta), 0},
        {0, 1, 0, 0},
        {-std::sin(theta), 0, std::cos(theta), 0},
        {0, 0, 0, 1}
    }};
}

int main(int argc, char* argv[]) {
    if (argc != 5) {
        std::cerr << "Usage: " << argv[0] << " <input filename.las/laz> <Resolution> <Viewing Angles> <Dimension to be rasterized>" << std::endl;
        return 0;
    }

    std::string input_filename = argv[1];
    double resolution = parse_res(argv[2]);
    std::vector<std::pair<double, double>> angles = parse_angles(argv[3]);
    std::string dim = argv[4];

    // Check if input_filename is empty
    if (input_filename.empty()) {
        std::cerr << "Error: input filename is empty!" << std::endl;
        return 0;
    }

    // Check if file exists
    std::ifstream file(input_filename);
    if (!file.good()) {
        std::cerr << "Error: input file does not exist: " << input_filename << std::endl;
        return 0;
    }
    file.close();

    double pi = 3.14159265359;

    std::cout << "Number of angles: " << angles.size() << std::endl;
    std::cout << "Resolution will be: " << resolution << std::endl;

    for (const auto& angle : angles) {
        double theta_x = angle.first * pi / 180;
        double theta_y = angle.second * pi / 180;

        Matrix4x4 tran_mat;

        if (theta_x != 0 && theta_y == 0) {
            tran_mat = Rmx_4x4(theta_x);
        } else if (theta_y != 0 && theta_x == 0) {
            tran_mat = Rmy_4x4(theta_y);
        } else {
            std::cerr << "Error: Only one axis rotation is allowed at a time." << std::endl;
            continue; // Skip this iteration if double-axis rotation is encountered
        }

        // Convert the transformation matrix to a space-separated string
        std::string matstring;
        for (const auto& row : tran_mat) {
            for (const auto& elem : row) {
                matstring += std::to_string(elem) + " ";
            }
        }

        // Remove trailing space
        if (!matstring.empty()) {
            matstring.pop_back();
        }

        pdal::PipelineManager pipelineManager;

        std::string pipeline = R"json({
            "pipeline": [
                {
                    "type": "readers.las",
                    "filename": ")" + input_filename + R"json("
                },
                {
                    "type": "filters.transformation",
                    "matrix": ")" + matstring + R"json("
                },
                {
                    "type": "filters.hexbin",
                    "edge_length": 0.5
                },
                {
                    "type": "writers.gdal",
                    "filename": "outputfile.tif",
                    "resolution": )json" + std::to_string(resolution) + R"json(,
                    "gdaldriver": "GTiff",
                    "output_type": "mean",
                    "dimension": ")" + dim + R"json("
                }
            ]
        })json";

        // Validate and execute the pipeline
        try {
            pipelineManager.readPipeline(pipeline);
            pipelineManager.execute();
        } catch (const pdal::pdal_error& e) {
            std::cerr << "PDAL Error: " << e.what() << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Standard Error: " << e.what() << std::endl;
        }
    }

    return 1;
}

