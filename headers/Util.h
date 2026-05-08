//
// Created by igor on 5/5/26.
//

#ifndef IAK_PREUREDITEV_GENOMA_UTIL_H
#define IAK_PREUREDITEV_GENOMA_UTIL_H
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>

namespace Util {

    inline void output(std::ofstream& file, const std::string& msg, const bool print=true) {
        if (print) {
            std::cout << msg;
            if (file) file << msg;
        }
    }

    inline void outputVector(std::ofstream& file, const std::vector<size_t>& vec, const bool print=true) {
        for (auto el : vec) {
            output(file, std::to_string(el) + " ", print);
        }
    }

    inline std::vector<size_t> readFile(const std::string& fileName) {
        std::vector<size_t> stringFile;

        std::ifstream file(fileName);
        if (!file.is_open()) {
            std::cerr << "Failed to open file: " << fileName << std::endl;
            return {};
        }

        while (!file.eof()) {
            std::string line;
            std::getline(file, line);

            try {
                stringFile.push_back(std::stoi(line));
            } catch (std::invalid_argument& e) {
                std::cerr << "File is in an incorrect format." << fileName << std::endl;
                return {};
            }
        }

        return stringFile;
    }

    inline void reverseTrack(std::vector<size_t> &genome, const size_t start, const size_t end) {
        auto startIt = genome.begin() + start;
        auto endIt = genome.begin() + end + 1;

        // To store the sliced vector.
        std::vector<size_t> result(endIt - startIt);
        std::copy(startIt, endIt, result.begin());
        std::reverse(result.begin(), result.end());

        // Replace rotated subvector in the genome.
        auto next_pos = genome.erase(startIt, endIt);
        genome.insert(next_pos, result.begin(), result.end());

        std::cout <<"";
    }

    inline bool isPermutationIdentity(const std::vector<size_t> vec) {
        for (size_t i = 0; i < vec.size(); i++) {
            if (vec[i] != i) return false;
        }

        return true;
    }

    inline std::vector<std::vector<size_t>> getTracks(std::vector<size_t>& genome) {

    }
}

#endif //IAK_PREUREDITEV_GENOMA_UTIL_H
