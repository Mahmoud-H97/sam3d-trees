#include <cstddef>
#include <opencv4/opencv2/opencv_modules.hpp>
//#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/core.hpp>
#include <opencv4/opencv2/imgcodecs.hpp>
#include <ostream>
#include <iostream>
#include <sys/types.h>
#include <vector>
#include <string>
#include "xyz.hpp"
#include "rgb.hpp"
#include "create_image.hpp"
#include "apply_rot.hpp"


// Function implementation for IFPC (ImageFromPointCloud)
void IFPC(const std::vector<xyz>& points, const std::vector<rgb>& colors, double resolution, const std::string& filename) {
    
    // Check if points and colors have the same size
    int pSize = points.size();
    int cSize = colors.size();
    if (pSize != cSize) {
    
    }
    if (points.size() != colors.size()) {
	std::cerr << "Error: Mismatch between points and colors size." << std::endl;
        return;
    }

    // Initialize variables to track the minimum and maximum x and y
    double xmin = points[0].x;
    double xmax = points[0].x;
    double ymin = points[0].y;
    double ymax = points[0].y;

    // Calculate the min and max of x and y
    for (const auto& point : points) {
        if (point.x < xmin) xmin = point.x;
        if (point.x > xmax) xmax = point.x;
        if (point.y < ymin) ymin = point.y;
        if (point.y > ymax) ymax = point.y;
    }

    // Calculate the width and height of the image
    int width = static_cast<int>((xmax - xmin) / resolution);
    int height = static_cast<int>((ymax - ymin) / resolution);

    // Create a new image filled with black pixels
    cv::Mat image(height, width, CV_8UC3, cv::Scalar(0, 0, 0));

    // Iterate over xyz points and rgb values
    for (size_t i = 0; i < points.size(); ++i) {
        int col = static_cast<int>((points[i].x - xmin) / resolution);
        int row = static_cast<int>((ymax - points[i].y) / resolution); // Adjust to image coordinate system

        // Check if the point is within bounds
        if (col >= 0 && col < width && row >= 0 && row < height) {
            // Set the pixel color using rgb values
            image.at<cv::Vec3b>(row, col) = cv::Vec3b(static_cast<u_char>(colors[i].b), static_cast<u_char>(colors[i].g), static_cast<u_char>(colors[i].r));
        }
    }

    // Save the image as a JPEG
    cv::imwrite(filename, image);
}



// to create an image based on 3d xyz coordinates and rgb values -> ImageFromPointCloud (IFPC)
/*
void IFPC (const std::vector<double>& x, const std::vector<double>& y, const std::vector<int>& r, const std::vector<int>& g,
	const std::vector<int>& b, double xmin, double ymin, double xmax, double ymax, double resolution, const std::string& filename) {

	//calc width and height 
	int width = static_cast<int>((xmax - xmin) / resolution);
	int height = static_cast<int>((ymax - ymin) / resolution);

	//a new image filled with black pixels
	cv::Mat image(height, width, CV_8UC3, cv::scalar(0,0,0));

	//iteration over xy points and rgb values
	for (size_t i = 0; i < x.size(); ++i) {
		int col = static_cast<int>((x[i] - xmin) / resolution);
		int row = static_cast<int>((ymax - y[i]) / resolution); //adjust to image coordinate sys!

		if (col >= 0 && col < width && row >= 0 && row < height) {
			//set the pixel color using rgb values
			image.at<cv::Vec3b>(row, col) = cv::Vec3b(static_cast<u_char>(b[i]), static_cast<u_char>(g[i]), static_cast<u_char>(r[i]));
		}
	}

	//save the image as JPEG
	cv::imwrite(filename, image);
}
*/
