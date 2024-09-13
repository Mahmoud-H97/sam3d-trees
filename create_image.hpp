#ifndef CREATE_IMAGE_HPP
#define CREATE_IMAGE_HPP

#include <vector>
#include <string>
#include "xyz.hpp"
#include "rgb.hpp"

// Function prototype for IFPC (ImageFromPointCloud)
void IFPC(const std::vector<xyz>& points, const std::vector<rgb>& colors, double resolution, const std::string& filename);

#endif 

