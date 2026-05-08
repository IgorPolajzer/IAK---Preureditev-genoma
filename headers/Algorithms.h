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
        std::vector<size_t> result;

        for (size_t i = 0; i < genome.size(); ++i) {
            size_t j = std::find(genome.begin(), genome.end(), i + 1) - genome.begin();

            if (i != j) {
                Util::reverseTrack(genome, i , j);
                Util::outputVector(outputFile, genome, true);
                Util::output(outputFile, "\n", true);
            }

            if (Util::isPermutationIdentity(genome)) return genome;
        }

        return genome;
    }

    inline std::vector<size_t> improvedBreakpointReversalSort(const std::string& fileName) {

    }

    inline std::vector<size_t> ownImprovedImplementation(const std::string& fileName) {

    }
}

#endif //IAK_PREUREDITEV_GENOMA_ALGORITHMS_H
