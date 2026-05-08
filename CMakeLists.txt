cmake_minimum_required(VERSION 4.2)
project(IAK_Preureditev_genoma)

set(CMAKE_CXX_STANDARD 20)

add_executable(IAK_Preureditev_genoma main.cpp
        headers/Algorithms.h
        headers/Util.h
        headers/Track.h)
