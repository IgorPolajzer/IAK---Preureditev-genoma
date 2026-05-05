//
// Created by igor on 5/5/26.
//

#ifndef IAK_PREUREDITEV_GENOMA_UTIL_H
#define IAK_PREUREDITEV_GENOMA_UTIL_H
#include <fstream>
#include <iostream>
#include <sstream>

namespace Util {

    inline void output(std::ostream& file, const std::string& msg, const bool print=true) {
        if (print) {
            std::cout << msg;
            if (file) file << msg;
        }
    }

    inline std::string readFile(const std::string& fileName) {
        std::string stringFile;

        std::ifstream file(fileName);
        if (!file.is_open()) {
            std::cerr << "Failed to open file: " << fileName << std::endl;
            return "";
        }

        std::ostringstream buffer;
        buffer << file.rdbuf();
        stringFile = buffer.str();
        stringFile = stringFile.substr(0, stringFile.find_last_not_of(" \t\n\r") + 1);

        return stringFile;
    }
}

#endif //IAK_PREUREDITEV_GENOMA_UTIL_H
