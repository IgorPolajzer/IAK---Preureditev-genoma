#include <filesystem>
#include <iostream>

#include "headers/Algorithms.h"

constexpr std::string OUTPUT_FOLDER = "results/";

int main(const int argc, char** argv) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " [-rs or -irs or -imp] <genome-file-path>" << std::endl;
        return 1;
    }
    
    const std::string modeFlag = argv[1];
    const std::string fileName = argv[2];

    std::vector<size_t> results;

    size_t pos = fileName.find('/');
    std::string outputFileName = fileName.substr(pos + 1);

    std::ofstream outputFile = std::ofstream(OUTPUT_FOLDER + outputFileName);
    if (modeFlag == "-rs") {
        results = Algorithms::simpleReversalSort(fileName);
    } else if (modeFlag == "-irs") {
        results = Algorithms::improvedSimpleReversalSort(fileName);
    } else if (modeFlag == "-imp") {
        results = Algorithms::ownImprovedImplementation(fileName);
    }

    std::filesystem::create_directories(OUTPUT_FOLDER);
    for (auto result : results) {
        Util::output(outputFile, std::to_string(result));
    }

    return 0;
}
