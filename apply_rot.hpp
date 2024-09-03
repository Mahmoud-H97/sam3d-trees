#ifndef APPLY_ROT_HPP
#define APPLY_ROT_HPP

#include <array>
#include <utility>
#include <vector>
#include "rot_mat.hpp"

//Define a 3D point type 

using Point3D = std::array<double, 3> ;

//Function
//

std::vector<Point3D> ApplyRotation(const std::vector<Point3D>& points, const Matrix3x3& Rmx, const Matrix3x3& Rmy, const Point3D& camera_pos);
std::pair<int, int> CalcOutDims(const std::vector<Point3D>& rotated_points, double resolution);

#endif
