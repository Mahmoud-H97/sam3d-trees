#include "las2xyz.hpp"
#include <iostream>
#include <ostream>
#include <pdal/PointView.hpp>
#include <pdal/Reader.hpp>
#include <pdal/StageFactory.hpp>
#include <fstream>

bool las2xyz(const std::string &input_filename, const std::string &output_filename){
	pdal::StageFactory factory;

	//the reader stage 
	pdal::Stage* reader = factory.createstage("readers.las");
	if (!reader) {
		std::cerr << "Failed to create LAS reader." << std::endl;
		return false;
	}

	//the inputfile
	pdal::Options options;
	options.add("filename", input_filename);
	reader->setOptions(options);

	//reading pipeline
	pdal::PointTable table;
	reader->prepare(table);
	pdal::PointViewSet pointViewSet = reader->execute(table);

	//open the output xyz file
	std::ofstream outfile(output_filename);
	if (!outfile.is_open()) {
		std::cerr << "Failed to open output folder" << output_filename<< std::endl;
		return false;
	}

	//loop over points & write
	//
	for (auto& pointView : pointViewSet) {
		for (pdal::PointId i = 0; i < pointView->size(); ++i) {
			double x = pointView->getFieldAS<double>(pdal::Dimension::Id::X, i);
			double y = pointView->getFieldAS<double>(pdal::Dimension::Id::Y, i);
			double z = pointView->getFieldAS<double>(pdal::Dimension::Id::Z, i);

			outfile << x << "" << y << "" << z << std::endl;
		
		}
	
	}

	//close the file
	outfile.close();
	return true;

}
