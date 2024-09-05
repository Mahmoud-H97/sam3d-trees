#include <cstddef>
#include <opencv4/opencv2/opencv_modules.hpp>
#include <opencv4/opencv2/opencv.hpp>
#include <sys/types.h>
#include <vector>
#include <string>
#include <cmath>

// to create an image based on 3d xyz coordinates and rgb values -> ImageFromPointCloud (IFPC)
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

