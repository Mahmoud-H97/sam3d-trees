
#include "las2rgb.hpp"
#include <iostream>
#include <ostream>
#include <pdal/PointView.hpp>
#include <pdal/Reader.hpp>
#include <pdal/StageFactory.hpp>
#include <fstream>
#include <string>

void las2rgb(const std::string &input_filename){
	pdal::StageFactory factory;

	//the reader stage 
	pdal::Stage* reader = factory.createStage("readers.las");
	if (!reader) {
		std::cerr << "Failed to create LAS reader." << std::endl;
		return;
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
	std::string output_filename = "tmp.rgb";
	std::ofstream outfile(output_filename);
	if (!outfile.is_open()) {
		std::cerr << "Failed to open output folder" << output_filename << std::endl;
		return;
	}

	//loop over points & write
	//
	for (auto& pointView : pointViewSet) {
		for (pdal::PointId i = 0; i < pointView->size(); ++i) {
			int r = pointView->getFieldAs<double>(pdal::Dimension::Id::Red, i);
			int g = pointView->getFieldAs<double>(pdal::Dimension::Id::Green, i);
			int b = pointView->getFieldAs<double>(pdal::Dimension::Id::Blue, i);

			outfile << r << " " << g << " " << b << std::endl;
		}
	}

	//close the file
	outfile.close();

}
