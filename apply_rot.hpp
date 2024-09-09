#ifndef APPLY_ROT_HPP
#define APPLY_ROT_HPP

#include <array>
#include <utility>
#include <vector>
#include "rot_mat.hpp"

//Define a 3D point type 

using Point3D = std::array<double, 3> ;

//Define a xyz point type
//

struct xyz { 
	double x, y, z;
};


//Function
//

std::vector<xyz> ApplyRotation(const std::vector<xyz>& points, const Matrix3x3& Rmx, const Matrix3x3& Rmy, const std::vector<double>& camera_pos);
std::pair<int, int> CalcOutDims(const std::vector<xyz>& rotated_points, double resolution);

#endif
