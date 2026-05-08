//
// Created by igor on 5/5/26.
//

#ifndef IAK_PREUREDITEV_GENOMA_UTIL_H
#define IAK_PREUREDITEV_GENOMA_UTIL_H
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>

#include "Track.h"

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

    inline std::vector<size_t> reverseTrack(std::vector<size_t> genome, const size_t start, const size_t end) {
        auto startIt = genome.begin() + start;
        auto endIt = genome.begin() + end + 1;

        // To store the sliced vector.
        std::vector<size_t> result(endIt - startIt);
        std::copy(startIt, endIt, result.begin());
        std::reverse(result.begin(), result.end());

        // Replace rotated subvector in the genome.
        auto next_pos = genome.erase(startIt, endIt);
        genome.insert(next_pos, result.begin(), result.end());

        return genome;
    }

    inline bool isPermutationIdentity(const std::vector<size_t>& vec) {
        if (vec.size() == 1) return true;

        for (size_t i = 0; i < vec.size(); i++) {
            if (vec[i] != i) return false;
        }

        return true;
    }

    inline bool isSequence(const std::vector<size_t>& vec) {
        if (vec.size() == 1) return true;

        for (size_t i = 1; i < vec.size(); i++) {
            if (vec[i] != vec[i-1] + 1) return false;
        }

        return true;
    }

    inline bool isTrack(std::vector<size_t>& vec) {
        return  isSequence(vec) || isSequence(reverseTrack(vec, 0, vec.size() - 1));
    }

    inline std::vector<Track> getTracks(std::vector<size_t>& genome) {
        std::vector<Track> tracks;

        for (int i = 1; i < genome.size(); i++) {
            std::vector<size_t> track;
            track.push_back(genome[i-1]);

            size_t j = i;
            while (isTrack(track) && j < genome.size()) {
                track.push_back(genome[j]);
                j++;
            }
            track.pop_back();

            // Substract 1 from both indexes since i starts with 1
            // Subtract an additional 1 from j since we pop_back the last element.
            tracks.push_back(Track(track, i - 1, j - 2));
            i += track.size() - 1;
        }

        return tracks;
    }

    inline size_t getBreakpointCount(const std::vector<Track>& tracks) {
        size_t count = 0;

        for (auto track : tracks) {
            if (tracks.size() != 1) count++;
        }

        return count;
    }

    inline bool tracksIncludeDesc(const std::vector<Track>& tracks) {
        bool includeDesc = false;

        for (auto track : tracks) {
            for (size_t i = 1; i < track.track.size(); i++) {
                if (track.track[i-1] < track.track[i]) includeDesc = true;
            }

            if (includeDesc) break;
        }

        return includeDesc;
    }

    inline std::vector<size_t> getApplicableTrack(std::vector<size_t> genome) {
        std::vector<size_t> track;

        auto tracks = getTracks(genome);
        size_t breakPointCount = getBreakpointCount(tracks);
        size_t newBreakPointCount = breakPointCount;

        size_t i = 0;
        while (newBreakPointCount >= breakPointCount || i < tracks.size()) {
            genome = reverseTrack(genome, tracks[i].startIndex, tracks[i].endIndex);
            tracks = getTracks(genome);
            newBreakPointCount = getBreakpointCount(tracks);
            i++;
        }

        return track;
    }
}

#endif //IAK_PREUREDITEV_GENOMA_UTIL_H
