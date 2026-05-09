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
        std::ranges::reverse(result);

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

    inline size_t getBreakpointCount(std::vector<size_t>& genome) {
        std::vector<Track> tracks = getTracks(genome);

        size_t count = 0;

        for (auto track : tracks) {
            if (tracks.size() != 1) count++;
        }

        return count;
    }

    inline std::vector<Track> getDescTracks(const std::vector<Track>& tracks) {
        std::vector<Track> descTracks;

        for (auto track : tracks) {
            for (size_t i = 1; i < track.track.size(); i++) {
                if (track.track[i] < track.track[i-1]) {
                    descTracks.push_back(track);
                    i += track.track.size() - 1;
                }
            }
        }

        return descTracks;
    }

    // Finds a track in the genome which minimizes the breakpoint count in genome and reverse it in the genome.
    inline std::vector<size_t> reverseApplicableTrack(std::vector<size_t> genome, const std::vector<Track>& descTracks) {
        std::vector<size_t> track;

        if (descTracks.empty()) return {};

        // Find the descendingTrack with the smallest number.
        Track descTrack;
        size_t smallestNumber = -1;
        for (auto track : descTracks) {
            for (auto val : track.track) {
                if (smallestNumber == -1 || val < smallestNumber) {
                    descTrack = track;
                    smallestNumber = val;
                }
            }
        }

        // Store the descending tracks end index because this is the smallest number.
        size_t descTrackFirstIndex = descTrack.endIndex;
        size_t descTrackSecondIndex = smallestNumber == 0 ? 0 :descTrackFirstIndex;

        Track endTrack;
        for (size_t i = 0; i < genome.size(); i++) {
            if (genome[i] == genome[descTrackFirstIndex] - 1) {
                descTrackFirstIndex = i;
                break;
            }
        }

        // Add 1 to track start index (find with genome referece indexes)
        if (descTrackFirstIndex < descTrackSecondIndex) {
            if (smallestNumber != 0) descTrackFirstIndex++;
            return reverseTrack(genome, descTrackFirstIndex, descTrackSecondIndex);
        }

        if (smallestNumber != 0) descTrackSecondIndex++;
        return reverseTrack(genome, descTrackSecondIndex, descTrackFirstIndex);
    }

    // Finds a track in the genome which minimizes the breakpoint count in genome and reverse it in the genome.
    inline std::vector<size_t> reverseApplicableTrackImproved(std::vector<size_t> genome, const std::vector<Track>& descTracks) {
        std::vector<size_t> track;

        if (descTracks.empty()) return {};

        // Find the descendingTrack with the smallest number.
        Track bestDescTrack;
        size_t bestNumberOfBreakpoints = -1;
        // Find the best descTrack
        for (auto descTrack : descTracks) {
            std::vector<size_t> changedGenome = reverseTrack(genome, descTrack.startIndex, descTrack.endIndex);
            size_t numberOfBreakpoints = getBreakpointCount(changedGenome);
            if (bestNumberOfBreakpoints == -1 || numberOfBreakpoints < bestNumberOfBreakpoints) {
                bestDescTrack = descTrack;
                bestNumberOfBreakpoints = numberOfBreakpoints;
            }
        }

        // Store the descending tracks end index because this is the smallest number.
        size_t descTrackFirstIndex = bestDescTrack.endIndex;
        size_t descTrackSecondIndex = descTrackFirstIndex;

        Track endTrack;
        for (size_t i = 0; i < genome.size(); i++) {
            if (genome[i] == genome[descTrackFirstIndex] - 1) {
                descTrackFirstIndex = i;
                break;
            }
        }

        // Add 1 to track start index (find with genome referece indexes)
        if (descTrackFirstIndex < descTrackSecondIndex) {
            descTrackFirstIndex++;
            return reverseTrack(genome, descTrackFirstIndex, descTrackSecondIndex);
        }

        descTrackSecondIndex++;
        return reverseTrack(genome, descTrackSecondIndex, descTrackFirstIndex);
    }

    inline std::vector<size_t> reverseAscending(std::vector<size_t> genome) {
        auto tracks = getTracks(genome);

        if (tracks.empty()) return {};

        // Find first rack which lenght is > 1.
        Track applicableTrack;

        for (auto track : tracks) {
            if (track.track.size() > 1 && std::find(track.track.begin(), track.track.end(), 0) == track.track.end()) {
                applicableTrack = track;
                break;
            }
        }

        return reverseTrack(genome, applicableTrack.startIndex, applicableTrack.endIndex);
    }
}

#endif //IAK_PREUREDITEV_GENOMA_UTIL_H
