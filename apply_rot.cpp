//This one is to apply the rotation matrices to the (x,y,z) coordinates
#include "apply_rot.hpp"
#include <algorithm>

std::vector<Point3D> ApplyRotation(const std::vector<Point3D> &points, const Matrix3x3 &Rmx, const Matrix3x3 &Rmy, const Point3D &camera_pos){

	std::vector<Point3D> rotated_points;

	for (const auto& point : points) {

		Point3D translated_points = {point[0] - camera_pos[0], point[1] - camera_pos[1], point[2] - camera_pos[2]};

		Point3D Rx;
		for (int i = 0; i<3; i++) {
			Rx[i] = Rmx[i][0] * translated_points[0] + 
				Rmx[i][1] * translated_points[1] +
				Rmx[i][2] * translated_points[2];
		}


		Point3D Ry;
		for (int i = 0; i<3; i++) {
			Ry[i] = Rmy[i][0] * Rx[0] + 
				Rmy[i][1] * Rx[1] +
				Rmy[i][2] * Rx[2];
		}


		rotated_points.push_back({Ry[0] + camera_pos[0], Ry[1] + camera_pos[1], Ry[2] + camera_pos[2]});
	
	}

	return rotated_points;

}

//calculate output dimension and range for the rotated points
//
std::pair<int, int> CalcOutDims(const std::vector<Point3D> &rotated_points, double resolution){
	double Rxmin = rotated_points[0][0];
	double Rxmax = rotated_points[0][0];
	double Rymin = rotated_points[0][1];
	double Rymax = rotated_points[0][1];

	for (const auto& point : rotated_points) {
	
	Rxmin = std::min(Rxmin, point[0]);
	Rxmax = std::max(Rxmax, point[0]);
	Rymin = std::min(Rymin, point[1]);
	Rymax = std::max(Rymax, point[1]);
	
	}

	Rxmin -= resolution;
	Rxmax += resolution;
	Rymin -= resolution;
	Rymax += resolution;

	int Rwidth = static_cast<int>((Rxmax - Rxmin) / resolution);
	int Rheight = static_cast<int>((Rymax -Rymin) / resolution);

	return {Rwidth, Rheight};

}
