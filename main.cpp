#include <filesystem>
#include <iostream>

#include "headers/Algorithms.h"

constexpr std::string OUTPUT_FOLDER = "results/";

void runAlgorithm(const std::string& modeFlag, const std::string& fileName) {
    std::vector<size_t> results;

    size_t pos = fileName.find('/');
    std::string outputFileName = fileName.substr(pos + 1);
    std::ofstream outputFile;
    size_t reverseCounter = 0;

    auto start = std::chrono::high_resolution_clock::now();
    if (modeFlag == "-rs") {
        std::filesystem::create_directories(OUTPUT_FOLDER + "simple_reversal_sort/");
        outputFile = std::ofstream(OUTPUT_FOLDER + "simple_reversal_sort/" + outputFileName);
        results = Algorithms::simpleReversalSort(fileName, outputFile, reverseCounter);
    } else if (modeFlag == "-ibrs") {
        std::filesystem::create_directories(OUTPUT_FOLDER + "improved_breakpoint_reversal_sort/");
        outputFile = std::ofstream(OUTPUT_FOLDER + "improved_breakpoint_reversal_sort/" + outputFileName);
        results = Algorithms::improvedBreakpointReversalSort(fileName, outputFile, reverseCounter);
    } else if (modeFlag == "-imp") {
        std::filesystem::create_directories(OUTPUT_FOLDER + "improved_custom_reversal_sort/");
        outputFile = std::ofstream(OUTPUT_FOLDER + "improved_custom_reversal_sort/" + outputFileName);
        results = Algorithms::ownImprovedImplementation(fileName, outputFile, reverseCounter);
    }

    auto stop = std::chrono::high_resolution_clock::now();
    const auto msDuration = duration_cast<std::chrono::milliseconds>(stop - start);
    const auto microsDuration = duration_cast<std::chrono::microseconds>(stop - start);

    Util::output(outputFile, "\nResult: ", true);
    Util::outputVector(outputFile, results, true);

    Util::output(
        outputFile,
        "\nExecution time: " +
        std::to_string(msDuration.count()) + " ms -> " +
        std::to_string(microsDuration.count()) + " us\n",
        true
    );

    Util::output(outputFile, "\nReverse counter: " + std::to_string(reverseCounter), true);
}

int main(const int argc, char** argv) {

    if (argc < 3) {
        std::cerr << "Usage: " << std::endl;
        std::cerr << "1.: " << argv[0] << " [-rs or -irs or -imp] <genome-file-path>" << std::endl;
        std::cerr << "2.: " << argv[0] << " [-t] [-rs or -irs or -imp]" << std::endl;
        return 1;
    }

    const std::string modeFlag = argv[1];
    const std::string fileName = argv[2];
    const std::string testAlgorithm = argv[2];

    if (modeFlag == "-t") {
        const std::vector<std::string> problemFiles = {
            "genom/G1.txt",
            "genom/G2.txt",
            "genom/G3.txt",
            "genom/G4.txt",
            "genom/G5.txt"
        };

        for (const auto& problemFile : problemFiles) {
            runAlgorithm(testAlgorithm, problemFile);
        }
    }

    runAlgorithm(modeFlag, fileName);
    
    return 0;
}
