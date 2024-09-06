#include <pdal/PipelineManager.hpp>
#include <pdal/PointView.hpp>
#include <iostream>
#include <fstream>

void las2xyz(const std::string &input_filename) {
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

