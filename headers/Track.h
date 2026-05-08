//
// Created by igor on 5/8/26.
//

#ifndef IAK_PREUREDITEV_GENOMA_TRACK_H
#define IAK_PREUREDITEV_GENOMA_TRACK_H
#include <vector>

struct Track {
    std::vector<size_t> track;
    size_t startIndex;
    size_t endIndex;
};

#endif //IAK_PREUREDITEV_GENOMA_TRACK_H
