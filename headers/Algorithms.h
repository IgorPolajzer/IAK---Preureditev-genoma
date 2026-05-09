//
// Created by igor on 5/5/26.
//

#ifndef IAK_PREUREDITEV_GENOMA_ALGORITHMS_H
#define IAK_PREUREDITEV_GENOMA_ALGORITHMS_H
#include <vector>
#include <bits/stdc++.h>

#include "Util.h"

namespace Algorithms {
    inline std::vector<size_t> simpleReversalSort(const std::string& fileName, std::ofstream& outputFile) {
        std::vector<size_t> genome = Util::readFile(fileName);

        for (size_t i = 0; i < genome.size(); ++i) {
            size_t j = std::find(genome.begin(), genome.end(), i + 1) - genome.begin();

            if (i != j) {
                genome = Util::reverseTrack(genome, i , j);
                Util::outputVector(outputFile, genome, true);
                Util::output(outputFile, "\n", true);
            }

            if (Util::isPermutationIdentity(genome)) return genome;
        }

        return genome;
    }

    inline std::vector<size_t> improvedBreakpointReversalSort(const std::string& fileName, std::ofstream& outputFile) {
        std::vector<size_t> genome = Util::readFile(fileName);

        // Add imaginary 0 and n+1 to the genome.
        genome.emplace(genome.begin(), 0);
        genome.push_back(genome.size());

        size_t breakpointCount = Util::getBreakpointCount(genome);

        while (breakpointCount > 0) {
            std::vector<Track> tracks = Util::getTracks(genome);
            std::vector<Track> descTracks = Util::getDescTracks(tracks);

            if (!descTracks.empty()) {
                genome = Util::reverseApplicableTrack(genome, descTracks);
            } else {
                genome = Util::reverseAscending(genome);
            }

            breakpointCount = Util::getBreakpointCount(genome);
            Util::outputVector(outputFile, genome, true);
            Util::output(outputFile, "\n", true);
        }

        genome.erase(genome.begin());
        genome.erase(genome.end());

        return genome;
    }

    inline std::vector<size_t> ownImprovedImplementation(const std::string& fileName, std::ofstream& outputFile) {
        std::vector<size_t> genome = Util::readFile(fileName);

        // Add imaginary 0 and n+1 to the genome.
        genome.emplace(genome.begin(), 0);
        genome.push_back(genome.size());

        size_t breakpointCount = Util::getBreakpointCount(genome);

        while (breakpointCount > 0) {
            std::vector<Track> tracks = Util::getTracks(genome);
            std::vector<Track> descTracks = Util::getDescTracks(tracks);

            if (!descTracks.empty()) {
                genome = Util::reverseApplicableTrackImproved(genome, descTracks);
            } else {
                genome = Util::reverseAscending(genome);
            }

            breakpointCount = Util::getBreakpointCount(genome);
            Util::outputVector(outputFile, genome, true);
            Util::output(outputFile, "\n", true);
        }

        genome.erase(genome.begin());
        genome.erase(genome.end());

        return genome;
    }
}

#endif //IAK_PREUREDITEV_GENOMA_ALGORITHMS_H
